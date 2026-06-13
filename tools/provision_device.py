#!/usr/bin/env python3
import argparse
import json
import secrets


def main() -> None:
    parser = argparse.ArgumentParser(description='Generate xmeshnet provisioning values.')
    parser.add_argument('--mesh-id', default=None, help='Mesh ID as AA-BB-CC-DD-EE-FF. Generated if omitted.')
    parser.add_argument('--mqtt-uri', default='mqtts://broker.example.com:8883')
    args = parser.parse_args()

    mesh_id = args.mesh_id or '-'.join(f'{b:02X}' for b in secrets.token_bytes(6))
    auth_key = secrets.token_hex(32)
    print(json.dumps({
        'mesh_id': mesh_id,
        'mesh_auth_key_hex': auth_key,
        'mqtt_uri': args.mqtt_uri,
    }, indent=2))


if __name__ == '__main__':
    main()
