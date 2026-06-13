export type DeviceRole = 'gateway' | 'sensor' | 'relay' | 'actuator';

export interface Device {
  meshId: string;
  nodeId: string;
  role: DeviceRole;
  name?: string;
}
