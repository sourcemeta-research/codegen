export type ConstTest_Properties_Version = "1.0.0";

export type ConstTest_Properties_OptionalFlag = false;

export type ConstTest_Properties_Nothing = null;

export type ConstTest_Properties_Nested_Properties_FixedValue = "fixed";

export type ConstTest_Properties_Nested_Properties_FixedNumber = 100;

export type ConstTest_Properties_Nested_AdditionalProperties = never;

export type ConstTest_Properties_Nested = {
  "fixedValue"?: ConstTest_Properties_Nested_Properties_FixedValue;
  "fixedNumber"?: ConstTest_Properties_Nested_Properties_FixedNumber;
} & {
  [K in string as K extends
    "fixedValue" |
    "fixedNumber"
  ? never : K]: ConstTest_Properties_Nested_AdditionalProperties;
};

export type ConstTest_Properties_Mode = "production";

export type ConstTest_Properties_Enabled = true;

export type ConstTest_Properties_Count = 42;

export type ConstTest_AdditionalProperties = never;

export type ConstTest = {
  "version": ConstTest_Properties_Version;
  "enabled": ConstTest_Properties_Enabled;
  "mode": ConstTest_Properties_Mode;
  "count": ConstTest_Properties_Count;
  "nothing": ConstTest_Properties_Nothing;
  "optionalFlag"?: ConstTest_Properties_OptionalFlag;
  "nested"?: ConstTest_Properties_Nested;
} & {
  [K in string as K extends
    "version" |
    "enabled" |
    "mode" |
    "count" |
    "nothing" |
    "optionalFlag" |
    "nested"
  ? never : K]: ConstTest_AdditionalProperties;
};
