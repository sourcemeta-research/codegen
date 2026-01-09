Codegen
=======

- Each input schema corresponds to a single `.d.ts` file
- 100% structurally map to TypeScript. Additional constraints might belong to
  validation

Supported JSON Schema Keywords (2020-12)
----------------------------------------

See https://www.learnjsonschema.com/2020-12/ for vocabulary documentation.

### Core

| Keyword | Support |
|---------|---------|
| `$schema` | Yes |
| `$id` | Yes |
| `$ref` | Yes |
| `$defs` | Yes |
| `$anchor` | No |
| `$dynamicAnchor` | No |
| `$dynamicRef` | No |
| `$vocabulary` | Ignored |
| `$comment` | Ignored |

### Applicator

| Keyword | Support |
|---------|---------|
| `properties` | Yes |
| `additionalProperties` | Yes |
| `items` | Yes |
| `prefixItems` | Yes |
| `anyOf` | Yes |
| `patternProperties` | No |
| `propertyNames` | Ignored |
| `dependentSchemas` | No |
| `contains` | Ignored |
| `allOf` | No |
| `oneOf` | No |
| `not` | No |
| `if` | No |
| `then` | No |
| `else` | No |

### Validation

| Keyword | Support |
|---------|---------|
| `type` | Yes |
| `enum` | Yes |
| `required` | Yes |
| `const` | Yes |
| `minLength` | Ignored |
| `maxLength` | Ignored |
| `pattern` | Ignored |
| `minimum` | Ignored |
| `maximum` | Ignored |
| `exclusiveMinimum` | Ignored |
| `exclusiveMaximum` | Ignored |
| `multipleOf` | Ignored |
| `minProperties` | Ignored |
| `maxProperties` | Ignored |
| `dependentRequired` | No |
| `minItems` | Ignored |
| `maxItems` | Ignored |
| `minContains` | Ignored |
| `maxContains` | Ignored |
| `uniqueItems` | Ignored |

### Unevaluated

| Keyword | Support |
|---------|---------|
| `unevaluatedItems` | No |
| `unevaluatedProperties` | No |

### Meta-Data

| Keyword | Support |
|---------|---------|
| `title` | Ignored |
| `description` | Ignored |
| `default` | Ignored |
| `deprecated` | Ignored |
| `examples` | Ignored |
| `readOnly` | Ignored |
| `writeOnly` | Ignored |

### Format Annotation

| Keyword | Support |
|---------|---------|
| `format` | Ignored |

### Content

| Keyword | Support |
|---------|---------|
| `contentEncoding` | Ignored |
| `contentMediaType` | Ignored |
| `contentSchema` | Ignored |
