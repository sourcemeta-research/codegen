# JSON Schema Codegen

> Convert JSON Schema to the type systems of a growing amount of programming
languages.

While this idea is not new, most community driven projects support only a basic
subset of JSON Schema, and often have various compliance issues.  In
comparison, this project is maintained by a member of the JSON Schema Technical
Steering Committee and aims for strict compliance and high coverage of the
specification.

## Keyword Support

Note that not every keyword can be directly mapped into a type system. We aims
for 100% structural coverage while you are expected to still validate the
instance against the schema using traditional JSON Schema evaluator to fully
apply any remaining assertions.

| Vocabulary | Keyword | TypeScript |
|------------|---------|------------|
| JSON Schema 2020-12 Core | `$schema` | Yes |
| JSON Schema 2020-12 Core | `$id` | Yes |
| JSON Schema 2020-12 Core | `$ref` | Yes |
| JSON Schema 2020-12 Core | `$defs` | Yes |
| JSON Schema 2020-12 Core | `$anchor` | Yes |
| JSON Schema 2020-12 Core | `$dynamicAnchor` | Pending |
| JSON Schema 2020-12 Core | `$dynamicRef` | Pending |
| JSON Schema 2020-12 Core | `$vocabulary` | Ignored |
| JSON Schema 2020-12 Core | `$comment` | Ignored |
| JSON Schema 2020-12 Applicator | `properties` | Yes |
| JSON Schema 2020-12 Applicator | `additionalProperties` | Yes |
| JSON Schema 2020-12 Applicator | `items` | Yes |
| JSON Schema 2020-12 Applicator | `prefixItems` | Yes |
| JSON Schema 2020-12 Applicator | `anyOf` | Yes |
| JSON Schema 2020-12 Applicator | `patternProperties` | **CANNOT SUPPORT** |
| JSON Schema 2020-12 Applicator | `propertyNames` | Ignored |
| JSON Schema 2020-12 Applicator | `dependentSchemas` | Pending |
| JSON Schema 2020-12 Applicator | `contains` | Ignored |
| JSON Schema 2020-12 Applicator | `allOf` | Pending |
| JSON Schema 2020-12 Applicator | `oneOf` | **CANNOT SUPPORT** |
| JSON Schema 2020-12 Applicator | `not` | **CANNOT SUPPORT** |
| JSON Schema 2020-12 Applicator | `if` | Pending |
| JSON Schema 2020-12 Applicator | `then` | Pending |
| JSON Schema 2020-12 Applicator | `else` | Pending |
| JSON Schema 2020-12 Validation | `type` | Yes |
| JSON Schema 2020-12 Validation | `enum` | Yes |
| JSON Schema 2020-12 Validation | `required` | Yes |
| JSON Schema 2020-12 Validation | `const` | Yes |
| JSON Schema 2020-12 Validation | `minLength` | Ignored |
| JSON Schema 2020-12 Validation | `maxLength` | Ignored |
| JSON Schema 2020-12 Validation | `pattern` | Ignored |
| JSON Schema 2020-12 Validation | `minimum` | Ignored |
| JSON Schema 2020-12 Validation | `maximum` | Ignored |
| JSON Schema 2020-12 Validation | `exclusiveMinimum` | Ignored |
| JSON Schema 2020-12 Validation | `exclusiveMaximum` | Ignored |
| JSON Schema 2020-12 Validation | `multipleOf` | Ignored |
| JSON Schema 2020-12 Validation | `minProperties` | Ignored |
| JSON Schema 2020-12 Validation | `maxProperties` | Ignored |
| JSON Schema 2020-12 Validation | `dependentRequired` | Pending |
| JSON Schema 2020-12 Validation | `minItems` | Ignored |
| JSON Schema 2020-12 Validation | `maxItems` | Ignored |
| JSON Schema 2020-12 Validation | `minContains` | Ignored |
| JSON Schema 2020-12 Validation | `maxContains` | Ignored |
| JSON Schema 2020-12 Validation | `uniqueItems` | Ignored |
| JSON Schema 2020-12 Unevaluated | `unevaluatedItems` | Pending |
| JSON Schema 2020-12 Unevaluated | `unevaluatedProperties` | Pending |
| JSON Schema 2020-12 Meta-Data | `title` | Ignored |
| JSON Schema 2020-12 Meta-Data | `description` | Ignored |
| JSON Schema 2020-12 Meta-Data | `default` | Ignored |
| JSON Schema 2020-12 Meta-Data | `deprecated` | Ignored |
| JSON Schema 2020-12 Meta-Data | `examples` | Ignored |
| JSON Schema 2020-12 Meta-Data | `readOnly` | Ignored |
| JSON Schema 2020-12 Meta-Data | `writeOnly` | Ignored |
| JSON Schema 2020-12 Format Annotation | `format` | Ignored |
| JSON Schema 2020-12 Format Assertion | `format` | Ignored |
| JSON Schema 2020-12 Content | `contentEncoding` | Ignored |
| JSON Schema 2020-12 Content | `contentMediaType` | Ignored |
| JSON Schema 2020-12 Content | `contentSchema` | Ignored |

Support for other JSON Schema dialects coming soon.
