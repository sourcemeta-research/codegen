Codegen
=======

- Each input schema corresponds to a single `.d.ts` file
- 100% structurally map to TypeScript. Additional constraints might belong to
  validation

Supported JSON Schema Keywords (2020-12)
----------------------------------------

See https://www.learnjsonschema.com/2020-12/ for vocabulary documentation.

### Core

| Keyword | Support | Notes |
|---------|---------|-------|
| `$schema` | Yes | Schema identification |
| `$id` | Yes | Schema identification |
| `$ref` | Yes | Generates type alias to target |
| `$defs` | Yes | Definition container |
| `$anchor` | No | |
| `$dynamicAnchor` | No | |
| `$dynamicRef` | No | |
| `$vocabulary` | No | |
| `$comment` | Ignored | Annotation only |

### Applicator

| Keyword | Support | Notes |
|---------|---------|-------|
| `properties` | Yes | Generates object members |
| `additionalProperties` | Yes | Generates intersection type |
| `items` | Yes | Generates array item type or tuple additional items |
| `prefixItems` | Yes | Generates tuple types |
| `anyOf` | Yes | Generates union types |
| `patternProperties` | No | |
| `propertyNames` | Ignored | Validation only |
| `dependentSchemas` | No | |
| `contains` | Ignored | Validation only |
| `allOf` | No | |
| `oneOf` | No | |
| `not` | No | |
| `if` | No | |
| `then` | No | |
| `else` | No | |

### Validation

| Keyword | Support | Notes |
|---------|---------|-------|
| `type` | Partial | `string`, `object`, `integer`, `number`, `array`. The `boolean` and `null` types are handled via `enum` |
| `enum` | Yes | Generates literal unions; `[null]` becomes `null`, `[true, false]` becomes `boolean` |
| `required` | Yes | Marks properties as required/optional |
| `const` | No | |
| `minLength` | Ignored | Validation only |
| `maxLength` | Ignored | Validation only |
| `pattern` | Ignored | Validation only |
| `minimum` | Ignored | Validation only |
| `maximum` | Ignored | Validation only |
| `exclusiveMinimum` | Ignored | Validation only |
| `exclusiveMaximum` | Ignored | Validation only |
| `multipleOf` | Ignored | Validation only |
| `minProperties` | Ignored | Validation only |
| `maxProperties` | Ignored | Validation only |
| `dependentRequired` | No | |
| `minItems` | Ignored | Validation only |
| `maxItems` | Ignored | Validation only |
| `minContains` | Ignored | Validation only |
| `maxContains` | Ignored | Validation only |
| `uniqueItems` | Ignored | Validation only |

### Unevaluated

| Keyword | Support | Notes |
|---------|---------|-------|
| `unevaluatedItems` | No | |
| `unevaluatedProperties` | No | |

### Meta-Data

| Keyword | Support | Notes |
|---------|---------|-------|
| `title` | Ignored | Annotation only |
| `description` | Ignored | Annotation only |
| `default` | Ignored | Annotation only |
| `deprecated` | Ignored | Annotation only |
| `examples` | Ignored | Annotation only |
| `readOnly` | Ignored | Annotation only |
| `writeOnly` | Ignored | Annotation only |

### Format Annotation

| Keyword | Support | Notes |
|---------|---------|-------|
| `format` | Ignored | Annotation only |

### Content

| Keyword | Support | Notes |
|---------|---------|-------|
| `contentEncoding` | Ignored | Annotation only |
| `contentMediaType` | Ignored | Annotation only |
| `contentSchema` | Ignored | Annotation only |
