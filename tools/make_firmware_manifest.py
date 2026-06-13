#!/usr/bin/env python3
import argparse
import hashlib
import json
from pathlib import Path


def main() -> None:
    parser = argparse.ArgumentParser(description='Create an xmeshnet firmware manifest.')
    parser.add_argument('image', type=Path)
    parser.add_argument('--version', required=True)
    args = parser.parse_args()

    data = args.image.read_bytes()
    print(json.dumps({
        'version': args.version,
        'file': args.image.name,
        'size': len(data),
        'sha256': hashlib.sha256(data).hexdigest(),
    }, indent=2))


if __name__ == '__main__':
    main()
