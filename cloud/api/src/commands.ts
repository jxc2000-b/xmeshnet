export interface Command {
  meshId: string;
  nodeId?: string;
  commandType: string;
  payload: Record<string, unknown>;
}
