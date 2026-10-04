# JSON Blueprint Node Redesign — Spec

Status: **Draft**. Items marked `[Proposed — unconfirmed]` are design choices awaiting maintainer sign-off.

## Goal

Make the JSON Blueprint nodes (`UJSONBlueprintLibrary`, `Source/ScooterUtilsBPLibrary`) consistent in pin order, value types, success semantics, invalid-input handling, and purity — without breaking existing Blueprint graphs or existing C++ callers until a planned major release.

## Constraints

1. **Blueprint compatibility.** Saved graphs connect pins by *name*. Reordering parameters, changing display labels, appending enum values, and adding new functions are safe. Changing a pin's type, switching a node between pure and exec, or changing an existing node's behavior is not.
2. **C++ source compatibility.** `UJSONBlueprintLibrary` has always been exported (`SCOOTERUTILSBPLIBRARYMODULE_API`), so C++ callers may exist. C++ calls are positional, and UFUNCTIONs can't be overloaded. Reordering parameters, adding parameters, or changing parameter types on an existing function breaks C++ callers, even where it's safe for Blueprints.
3. Anything that violates either constraint goes into a new node set (Phase 2), with the old nodes deprecated and removed only in a major release (Phase 3).

## Current Inconsistencies

| # | Inconsistency | Phase |
|---|---------------|-------|
| 1 | **Add Field** takes every value as a String, while the getters return typed values (Float, Bool). | 2 |
| 2 | Array nodes are string-based in both directions. Number arrays read back as text (`"100.0"`). | 2 |
| 3 | Creation uses one dropdown node (**Add Field**); parsing uses separate typed getters. | 2 |
| 4 | `EJSONArrayType` has no Boolean, although `EJSONFieldType` does. | 1 |
| 5 | The type dropdown is the first pin on **Add Field**, **Add Array Field**, and **Get Array Field**; elsewhere **JSON String** comes first. | 2 (reorder breaks C++) |
| 6 | Getter success means "field exists" for String/Number/Boolean, but "exists and is the right type" for Array/Object. | 2 |
| 7 | Only **Remove Field** reports failure among the creation nodes. | 2 (new output breaks C++) |
| 8 | Invalid input: add nodes reset to `{}`, which loses data. Remove/Pretty/Minify return the input unchanged. Merge mixes both. | 2 |
| 9 | Validity checks are pure, but the getters and creation nodes have exec pins. | 2 |
| 10 | Pin labels: the getters' bool is an unnamed **Return Value**; Merge's inputs are **JSON String 1/2**; `GetObjectField` carries a redundant `DisplayName`. | 1 |
| 11 | Numbers are single-precision `float`. | 2 (type change) |

## Phase 1 — Non-breaking fixes (in place)

Changes to `UJSONBlueprintLibrary` that keep every existing Blueprint graph and C++ call compiling unchanged.

1. **Boolean arrays.** Append `Boolean UMETA(DisplayName = "Boolean Array")` to the end of `EJSONArrayType`. Don't reorder the existing values.
   - **Add Array Field** with **Boolean Array**: each value is converted with the same rule as **Add Field** Boolean (`FString::ToBool`: `true`/`yes`/`on` or non-zero becomes `true`).
   - **Get Array Field** with **Boolean Array**: each boolean element is returned as `"true"` or `"false"`. Elements that aren't booleans are skipped, matching how **Object Array** treats non-objects. `[Proposed — unconfirmed]`
2. **Pin labels.** These are display-only, via `ReturnDisplayName` and `UPARAM(DisplayName = ...)`. Internal pin names, and so existing connections, don't change.
   - **Get String / Number / Boolean / Array / Object Field** and **Get All Field Names**: return pin shown as **Success**.
   - **Is Valid JSON**: **Is Valid**. **Has Field**: **Has Field**. **Is Field Null**: **Is Null**.
   - **Merge JSON** inputs: **Base JSON** and **Overlay JSON**. `[Proposed — unconfirmed]`
3. **Cleanup.** Remove the redundant `meta = (DisplayName = "Get Object Field")`. The generated name is identical.
4. **Docs.** Update `docs/guide/blueprint-nodes/json/` (pin names, Boolean Array) and `docs/guide/cpp/json.md` (the enum value).

**Acceptance criteria**
- Given a Blueprint saved with the current nodes, when it's opened after Phase 1, then it compiles with every connection intact and no new warnings.
- Given C++ code calling `UJSONBlueprintLibrary` today, when it's rebuilt against Phase 1, then it compiles unchanged.
- Given `Add Array Field(Boolean Array, "", "flags", ["true","0","yes"])`, the output is `{"flags":[true,false,true]}`. Reading it back with **Get Array Field** (**Boolean Array**) returns `["true","false","true"]` and **Success** is `true`.

## Phase 2 — Redesigned node set + deprecation

### New class

`[Proposed — unconfirmed]` A new exported class `USUJSONLibrary` (`Public/SUJSONLibrary.h`, `Private/SUJSONLibrary.cpp`), using the module's `SU` prefix like `USUDebugPrint`. It goes in the existing categories, **Scooter Utilities > JSON > Creation** and **> Parsing**. A new class lets the new nodes reuse clear names, such as **Remove Field** and **Merge JSON**, without clashing with the old C++ symbols.

### Uniform rules

| Rule | Behavior |
|------|----------|
| R1 Pin order | **JSON String** first, then **Field Name**, then value input(s). Outputs: **JSON String Out** (creation) or the value (parsing), then **Success**. |
| R2 Purity | Every new node is `BlueprintPure`: they're string transforms with no side effects. `[Proposed — unconfirmed]` |
| R3 Empty input | An empty **JSON String** on a creation node starts a new object `{}`. |
| R4 Invalid input | A non-empty **JSON String** that isn't a valid JSON object is returned **unchanged**, with **Success** `false`. Nothing is ever silently reset. |
| R5 Success (creation) | `true` only if the operation was applied. **Remove Field** on a missing field is `false`, with the JSON unchanged. |
| R6 Success (parsing) | `true` only if the field exists **and** has the requested type. On failure the value output is its default (`""`, `0`, `false`, empty array). |
| R7 Numbers | `double` everywhere, matching `FJsonValueNumber` storage and UE5 Blueprint real numbers. |
| R8 Typed values | Values go in and come out typed. No string-encoded numbers or booleans. |
| R9 Top level | JSON objects only (`{...}`), unchanged from today. |
| R10 Output format | Compact JSON from creation nodes (unchanged); **Pretty Print JSON** is the only formatted output. |

### Node list

Every signature is `static`. `bool& bSuccess` is shown as **Success**. Creation nodes return `FString` shown as **JSON String Out**.

**Creation**

| Node | Signature (after `JSONString`, `FieldName`) | Notes |
|------|---------------------------------------------|-------|
| Add String Field | `const FString& Value, bool& bSuccess` | |
| Add Number Field | `double Value, bool& bSuccess` | |
| Add Boolean Field | `bool Value, bool& bSuccess` | |
| Add Null Field | `bool& bSuccess` | |
| Add Object Field | `const FString& ObjectJSON, bool& bSuccess` | Invalid `ObjectJSON` → unchanged, `false` (today it nests `{}`). |
| Add String Array Field | `const TArray<FString>& Values, bool& bSuccess` | |
| Add Number Array Field | `const TArray<double>& Values, bool& bSuccess` | |
| Add Boolean Array Field | `const TArray<bool>& Values, bool& bSuccess` | |
| Add Object Array Field | `const TArray<FString>& ObjectJSONs, bool& bSuccess` | Any invalid element → unchanged, `false` (today invalid elements are skipped). |
| Remove Field | `bool& bSuccess` | |
| Merge JSON | `(const FString& BaseJSON, const FString& OverlayJSON, bool& bSuccess)` | Shallow merge; overlay wins. Either input invalid → `BaseJSON` unchanged, `false`. |
| Pretty Print JSON | `(const FString& JSONString, bool& bSuccess)` | |
| Minify JSON | `(const FString& JSONString, bool& bSuccess)` | |

**Parsing** (return `bool` shown as **Success** unless noted)

| Node | Signature (after `JSONString`, `FieldName`) |
|------|---------------------------------------------|
| Is Valid JSON | `(const FString& JSONString)` → **Is Valid** |
| Has Field | → **Has Field** |
| Is Field Null | → **Is Null** |
| Get String Field | `FString& Value` |
| Get Number Field | `double& Value` |
| Get Boolean Field | `bool& Value` |
| Get Object Field | `FString& ObjectJSON` |
| Get String Array Field | `TArray<FString>& Values` |
| Get Number Array Field | `TArray<double>& Values` |
| Get Boolean Array Field | `TArray<bool>& Values` |
| Get Object Array Field | `TArray<FString>& ObjectJSONs` |
| Get All Field Names | `(const FString& JSONString, TArray<FString>& FieldNames)` |

Typed array getters succeed only if the field is an array **and every element** has the requested type. Otherwise `Values` is empty and **Success** is `false`.

`[Proposed — unconfirmed]` **Get Field Type** `(JSONString, FieldName, EJSONValueType& Type)` → **Success**, with a new `EJSONValueType { None, Null, String, Number, Boolean, Array, Object }`. With strict getters, callers need a way to inspect unknown data. Optional: drop it if it isn't wanted.

### Deprecating the old nodes

- Each `UJSONBlueprintLibrary` UFUNCTION gets `meta = (DeprecatedFunction, DeprecationMessage = "...")`, naming its replacement. For example: `"Use Add String Field, Add Number Field, or Add Boolean Field (Scooter Utilities > JSON)."` Existing graphs keep working and show a compile warning. The old nodes leave the node browser.
- The old class's category becomes **Scooter Utilities > JSON (Deprecated)**. Changing a category is safe.
- C++ declarations get `UE_DEPRECATED(<plugin version>, "...")` so C++ callers see compiler warnings too. **Verify** that UHT accepts `UE_DEPRECATED` on these UFUNCTION declarations in UE 5.5–5.8 before relying on it.
- Old implementations stay byte-for-byte in behavior. Don't route them through the new code if that would change any result.

### Old → new mapping

| Old node | Replacement |
|----------|-------------|
| Add Field (String / Number / Boolean) | Add String / Number / Boolean Field |
| Add Array Field (String / Number / Object / Boolean Array) | Add String / Number / Object / Boolean Array Field |
| Add Object Field, Add Null Field, Remove Field, Merge JSON, Pretty Print JSON, Minify JSON | Same-named node in `USUJSONLibrary` |
| Is Valid JSON, Has Field, Is Field Null, Get All Field Names | Same-named node in `USUJSONLibrary` |
| Get String / Number / Boolean / Object Field | Same-named node (strict type check, `double` for numbers) |
| Get Array Field | Get String / Number / Boolean / Object Array Field |

### Docs (Phase 2)

- Rewrite `docs/guide/blueprint-nodes/json/` (overview, creation, parsing, examples) for the new nodes and rules.
- Add **Migrating from the Legacy JSON Nodes** (`docs/guide/blueprint-nodes/json/migration.md`) with the mapping table and the behavior differences (R4, R6, R7).
- Move the current node reference into a **Legacy JSON Nodes** page, marked deprecated, until Phase 3.
- Update `docs/guide/cpp/json.md` for `USUJSONLibrary`, with a deprecation note on `UJSONBlueprintLibrary`.

**Acceptance criteria**
- Given a Blueprint saved with the old nodes, when it's opened after Phase 2, then it compiles with connections intact and shows deprecation warnings naming each replacement. Outputs are identical to before.
- Given C++ code calling `UJSONBlueprintLibrary`, when it's rebuilt, then it compiles with deprecation warnings only.
- Given `Add Number Field("not json", "x", 1)`, then **JSON String Out** is `not json` and **Success** is `false`.
- Given `{"n":"12"}`, then **Get Number Field**(`n`) gives **Success** `false` and **Value** `0`.
- Given `{"a":[1,"two"]}`, then **Get Number Array Field**(`a`) gives **Success** `false` and an empty **Values**.
- The node browser shows only the new nodes under **Scooter Utilities > JSON**.

## Phase 3 — Remove the deprecated nodes (future major release)

- Delete `UJSONBlueprintLibrary`, `EJSONFieldType` and `EJSONArrayType`, which the new design doesn't use.
- **Breaking:** graphs still using old nodes, or variables of the removed enum types, will fail to compile.
- Commit and PR type: `chore!:` with a `BREAKING CHANGE:` footer, so Release-Please bumps the **major** version.
- Docs: remove the **Legacy JSON Nodes** page; keep the migration page; call out the removal in the release notes.
- Precondition `[Proposed — unconfirmed]`: Phase 2 has shipped in at least one released minor version first.

## Testing

There's no Unreal automation harness yet. Each phase's PR carries manual steps that check the acceptance criteria above, including opening a Blueprint built with the previous version. Once a harness exists, these criteria should become automation tests, with a fixture Blueprint saved against the old nodes.

## Open Questions

1. Class name and file names for the new library (`USUJSONLibrary`).
2. Whether new nodes should be pure (R2), or keep exec pins on creation nodes so evaluation order is explicit in graphs.
3. Whether to include **Get Field Type** / `EJSONValueType`.
4. Phase 1 **Get Array Field** (**Boolean Array**): skip non-boolean elements (proposed), or convert them.
5. Merge input labels (**Base JSON** / **Overlay JSON**).
6. Deprecation window before Phase 3.
