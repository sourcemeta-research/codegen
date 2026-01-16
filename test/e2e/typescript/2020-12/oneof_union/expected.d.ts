export type OneOfTest_Properties_Value_OneOf_ZIndex2 = boolean;

export type OneOfTest_Properties_Value_OneOf_ZIndex1 = number;

export type OneOfTest_Properties_Value_OneOf_ZIndex0 = string;

export type OneOfTest_Properties_Value =
  OneOfTest_Properties_Value_OneOf_ZIndex0 |
  OneOfTest_Properties_Value_OneOf_ZIndex1 |
  OneOfTest_Properties_Value_OneOf_ZIndex2;

export type OneOfTest_Properties_Status_OneOf_ZIndex1 = "completed" | "cancelled";

export type OneOfTest_Properties_Status_OneOf_ZIndex0 = "pending" | "active";

export type OneOfTest_Properties_Status =
  OneOfTest_Properties_Status_OneOf_ZIndex0 |
  OneOfTest_Properties_Status_OneOf_ZIndex1;

export type OneOfTest_AdditionalProperties = never;

export interface OneOfTest {
  "value": OneOfTest_Properties_Value;
  "status"?: OneOfTest_Properties_Status;
}
