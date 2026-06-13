export interface TelemetryEvent {
  meshId: string;
  nodeId: string;
  eventType: string;
  payload: Record<string, unknown>;
  receivedAt: string;
}
