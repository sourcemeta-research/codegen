export type Person_Properties_Name = string;

export type Person_Properties_Age = number;

export type Person_AdditionalProperties = string;

export type Person = {
  "name": Person_Properties_Name;
  "age"?: Person_Properties_Age;
} & {
  [K in string as K extends
    "name" |
    "age"
  ? never : K]: Person_AdditionalProperties;
};
