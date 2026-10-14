#!/usr/bin/env python3
"""Pin source checkouts, then verify every recorded build dependency against the lock."""

import argparse
import os
from pathlib import Path
import subprocess


def canonical(url):
    return url.rstrip("/").removesuffix(".git").lower()


def read_revisions(path):
    revisions = {}
    for line in Path(path).read_text().splitlines():
        if line.strip() and not line.startswith("#"):
            url, revision = line.split()
            revisions[canonical(url)] = revision
    return revisions


def git(path, *args):
    return subprocess.check_output(["git", "-C", str(path), *args], text=True).strip()


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("mode", choices=["checkout", "verify"])
    parser.add_argument("lock")
    parser.add_argument("source")
    args = parser.parse_args()
    expected = read_revisions(args.lock)
    if args.mode == "verify":
        actual = read_revisions(args.source)
        if actual != expected:
            differences = [
                f"{url}: expected {expected.get(url)}, got {actual.get(url)}"
                for url in sorted(expected.keys() | actual.keys())
                if expected.get(url) != actual.get(url)
            ]
            raise SystemExit("Dependency mismatch:\n" + "\n".join(differences))
        print(f"Verified {len(actual)} locked dependency revisions.")
        return

    for root, directories, files in os.walk(args.source):
        if ".git" not in directories and ".git" not in files:
            continue
        if ".git" in directories:
            directories.remove(".git")
        url = canonical(git(root, "config", "--get", "remote.origin.url"))
        if url not in expected:
            raise SystemExit(f"Unpinned source repository: {url} ({root})")
        revision = expected[url]
        # Fetching the exact revision also works with shallow setup checkouts.
        subprocess.run(["git", "-C", root, "fetch", "origin", revision], check=True)
        subprocess.run(["git", "-C", root, "checkout", "--detach", revision], check=True)
        print(f"Pinned {url} to {revision}", flush=True)


if __name__ == "__main__":
    main()
