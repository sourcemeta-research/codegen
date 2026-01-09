export type VocabTest_Properties_Value = number;

export type VocabTest_Properties_Optional = boolean;

export type VocabTest_Properties_Name = string;

export type VocabTest_AdditionalProperties = never;

export type VocabTest = {
  "name": VocabTest_Properties_Name;
  "value": VocabTest_Properties_Value;
  "optional"?: VocabTest_Properties_Optional;
} & {
  [K in string as K extends
    "name" |
    "value" |
    "optional"
  ? never : K]: VocabTest_AdditionalProperties;
};
