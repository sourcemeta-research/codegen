export type ApiResponseMeta = ApiResponseHttpsexamplecomschemasmetadata;

export type ApiResponseData = ApiResponseHttpsexamplecomschemasuser;

export type ApiResponseAdditionalProperties = never;

export type ApiResponseHttpsexamplecomschemasuserName = string;

export type ApiResponseHttpsexamplecomschemasuserId = number;

export type ApiResponseHttpsexamplecomschemasuserEmail = ApiResponseHttpsexamplecomschemasemail;

export type ApiResponseHttpsexamplecomschemasuserAdditionalProperties = never;

export interface ApiResponseHttpsexamplecomschemasuser {
  "id": ApiResponseHttpsexamplecomschemasuserId;
  "name": ApiResponseHttpsexamplecomschemasuserName;
  "email"?: ApiResponseHttpsexamplecomschemasuserEmail;
}

export type ApiResponseHttpsexamplecomschemasmetadataVersion = number;

export type ApiResponseHttpsexamplecomschemasmetadataTimestamp = string;

export type ApiResponseHttpsexamplecomschemasmetadataAdditionalProperties = never;

export interface ApiResponseHttpsexamplecomschemasmetadata {
  "timestamp"?: ApiResponseHttpsexamplecomschemasmetadataTimestamp;
  "version"?: ApiResponseHttpsexamplecomschemasmetadataVersion;
}

export type ApiResponseHttpsexamplecomschemasemail = string;

export interface ApiResponse {
  "data": ApiResponseData;
  "meta": ApiResponseMeta;
}
