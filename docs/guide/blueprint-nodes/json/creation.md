# JSON Creation Nodes

Reference for the nodes that build and modify JSON strings.

**Category:** **Scooter Utilities** > **JSON** > **Creation**

Creation nodes build JSON from scratch or modify existing JSON. Each one takes a JSON string and returns an updated copy through its **JSON String Out** pin, so you can chain them together to build complex structures. The output is compact JSON on a single line. Use [Pretty Print JSON](#pretty-print-json) when you want it readable.

> [!WARNING]
> If the **JSON String** input isn't a valid JSON object, the add nodes start over with a new, empty object. Use [Is Valid JSON](./parsing#is-valid-json) first if you're not sure what you're passing in.

## Add Field

The workhorse of JSON creation. Adds a field to your JSON, with a type you pick from a dropdown.

| Pin | Direction | Description |
| --- | --------- | ----------- |
| **Field Type** | Input | **String**, **Number**, or **Boolean**. |
| **JSON String** | Input | The existing JSON. Leave empty to start a new object. |
| **Field Name** | Input | The name of the field, like `health`, `score`, or `name`. If the field already exists, its value is replaced. |
| **Value** | Input | The value as a string. It's converted based on **Field Type**. |
| **JSON String Out** | Output | The updated JSON. |

```
// Adding a string
Add Field(String, "", "name", "Bob")
→ {"name":"Bob"}

// Adding a number
Add Field(Number, "", "health", "100")
→ {"health":100}

// Adding a boolean
Add Field(Boolean, "", "alive", "true")
→ {"alive":true}

// Chaining them together
"" → Add Field(String, -, "name", "Bob")
   → Add Field(Number, -, "health", "100")
   → Add Field(Boolean, -, "alive", "true")
→ {"name":"Bob","health":100,"alive":true}
```

**Tips:**

* **Numbers:** A value that isn't a number, like `hello`, becomes `0`. Garbage in, zero out.
* **Numbers:** Values are converted with single-precision (float) accuracy, so very large whole numbers and some decimals may not round-trip exactly.
* **Booleans:** `true`, `yes`, and `on` (in any case) and any non-zero number become `true`. Everything else becomes `false`.

## Add Array Field

For when you need a list. Adds an array of strings, numbers, or entire JSON objects.

| Pin | Direction | Description |
| --- | --------- | ----------- |
| **Array Type** | Input | **String Array**, **Number Array**, or **Object Array**. |
| **JSON String** | Input | The existing JSON. |
| **Field Name** | Input | The name of the array field. |
| **Values** | Input | An array of strings. Each one is converted based on **Array Type**. |
| **JSON String Out** | Output | The updated JSON. |

```
// String array (player inventory items)
Add Array Field(String Array, "", "inventory", ["sword", "potion", "shield"])
→ {"inventory":["sword","potion","shield"]}

// Number array (high scores)
Add Array Field(Number Array, "", "scores", ["100", "250", "175"])
→ {"scores":[100,250,175]}

// Object array (list of players)
Player1 = {"name":"Alice","score":100}
Player2 = {"name":"Bob","score":200}
Add Array Field(Object Array, "", "players", [Player1, Player2])
→ {"players":[{"name":"Alice","score":100},{"name":"Bob","score":200}]}
```

**Tips:**

* Object arrays are super useful for lists of enemies, items, players, and so on.
* In an **Object Array**, any value that isn't a valid JSON object is skipped.
* Empty arrays are totally fine: `[]`.

## Add Object Field

Nesting dolls, JSON edition. Puts one JSON object inside another, which is great for grouping related data.

| Pin | Direction | Description |
| --- | --------- | ----------- |
| **JSON String** | Input | The parent JSON. |
| **Field Name** | Input | The name of the nested object field. |
| **Nested JSON** | Input | The JSON object to nest. If it isn't valid, an empty object `{}` is nested instead. |
| **JSON String Out** | Output | The updated JSON. |

```
// Create position data
Position = "" → Add Field(Number, -, "X", "100")
              → Add Field(Number, -, "Y", "200")
              → Add Field(Number, -, "Z", "50")
→ {"X":100,"Y":200,"Z":50}

// Add it to player data
PlayerData = "" → Add Field(String, -, "name", "Hero")
                → Add Object Field(-, "position", Position)
→ {"name":"Hero","position":{"X":100,"Y":200,"Z":50}}
```

**Tips:**

* Build the inner objects first, then nest them.
* You can nest as deep as you want (but maybe don't go crazy).
* Perfect for vectors, rotators, or any grouped data.

## Add Null Field

Sometimes nothing is something. Adds a field with a `null` value, for when you want to say "this field exists but has no value."

| Pin | Direction | Description |
| --- | --------- | ----------- |
| **JSON String** | Input | The existing JSON. |
| **Field Name** | Input | The name of the null field. |
| **JSON String Out** | Output | The updated JSON. |

```
Add Null Field("", "middleName")
→ {"middleName":null}
```

**Tips:**

* Null is different from an empty string `""` or zero.
* Use it when a value is optional but you want to track that the field exists.
* Check for it later with [Is Field Null](./parsing#is-field-null).

## Remove Field

The eraser. Removes a field from your JSON and tells you whether it actually found something to remove.

| Pin | Direction | Description |
| --- | --------- | ----------- |
| **JSON String** | Input | The JSON to modify. |
| **Field Name** | Input | The field to remove. |
| **Success** | Output | **true** if the field existed and was removed. |
| **JSON String Out** | Output | The JSON with the field removed. If **JSON String** isn't valid JSON, it's returned unchanged. |

```
JSON = {"name":"Bob","age":25,"temp":99}
Remove Field(JSON, "temp")
→ {"name":"Bob","age":25}
→ Success: true
```

## Merge JSON

Smooshes two JSON objects together. Fields from the second object overwrite any matching fields in the first.

| Pin | Direction | Description |
| --- | --------- | ----------- |
| **JSON String 1** | Input | The base JSON. |
| **JSON String 2** | Input | The JSON to merge in. |
| **JSON String Out** | Output | The combined JSON. |

```
JSON1 = {"name":"Bob","age":25}
JSON2 = {"age":26,"score":100}

Merge JSON(JSON1, JSON2)
→ {"name":"Bob","age":26,"score":100}
```

**Tips:**

* The second JSON wins on conflicts (`age` became `26`).
* Great for applying updates or patches.
* Nested objects aren't merged. A nested object in the second JSON replaces the one in the first.
* If **JSON String 2** isn't valid, you get **JSON String 1** back.

## Pretty Print JSON

Makes it look nice. Formats JSON with indentation and line breaks, which is perfect for debugging or saving human-readable files.

| Pin | Direction | Description |
| --- | --------- | ----------- |
| **JSON String** | Input | The JSON to format. |
| **JSON String Out** | Output | The formatted JSON, indented with tabs. If the input isn't valid JSON, it's returned unchanged. |

```
Before: {"name":"Bob","health":100,"alive":true}

After:
{
	"name": "Bob",
	"health": 100,
	"alive": true
}
```

**Tips:**

* Use it before saving files that people need to read or edit, like config files.
* It doesn't change the data, just the formatting.

## Minify JSON

Strips all the whitespace. Removes formatting, indentation, and line breaks to make JSON compact for storage or sending over a network.

| Pin | Direction | Description |
| --- | --------- | ----------- |
| **JSON String** | Input | The JSON to minify. |
| **JSON String Out** | Output | The compact JSON. If the input isn't valid JSON, it's returned unchanged. |

```
Before:
{
	"name": "Bob",
	"health": 100,
	"alive": true
}

After: {"name":"Bob","health":100,"alive":true}
```

**Tips:**

* Use it before saving to disk to reduce file size, or before sending data where size matters.
* It's the opposite of **Pretty Print JSON**. The data is identical, only the formatting changes.
