# JSON Parsing Nodes

Reference for the nodes that validate JSON and read values out of it.

**Category:** **Scooter Utilities** > **JSON** > **Parsing**

Parsing nodes read and extract data from JSON strings. The getter nodes return **true** when they find the field, and put the value on an output pin.

> [!NOTE]
> Field names are case-sensitive: `Name` and `name` are different fields.

## Is Valid JSON

The gatekeeper. Checks whether a string is a valid JSON object before you try to parse it.

| Pin | Direction | Description |
| --- | --------- | ----------- |
| **JSON String** | Input | The string to validate. |
| **Return Value** | Output | **true** if the string is a valid JSON object. |

```
Is Valid JSON('{"name":"Bob"}')  → true
Is Valid JSON('not json at all') → false
Is Valid JSON('{"broken":}')     → false
Is Valid JSON('[1,2,3]')         → false (top-level arrays aren't supported)
```

**Tips:**

* Always check JSON that comes from outside sources, like files, web APIs, or user input.
* Returns **false** for empty strings.

## Has Field

Does this field exist? Checks whether a specific field exists in the JSON.

| Pin | Direction | Description |
| --- | --------- | ----------- |
| **JSON String** | Input | The JSON to check. |
| **Field Name** | Input | The field to look for. |
| **Return Value** | Output | **true** if the field exists. |

```
JSON = {"name":"Bob","age":25}

Has Field(JSON, "name")  → true
Has Field(JSON, "email") → false
```

**Tips:**

* Works for any field type, including `null` fields.
* Returns **false** if the JSON is invalid.

## Is Field Null

Is this field intentionally empty? Checks whether a field exists and has a `null` value.

| Pin | Direction | Description |
| --- | --------- | ----------- |
| **JSON String** | Input | The JSON to check. |
| **Field Name** | Input | The field to check. |
| **Return Value** | Output | **true** if the field exists and is `null`. |

```
JSON = {"name":"Bob","email":null}

Is Field Null(JSON, "email")   → true
Is Field Null(JSON, "name")    → false
Is Field Null(JSON, "missing") → false (doesn't exist)
```

## Get String Field

Extracts text. Gets a string value from the JSON.

| Pin | Direction | Description |
| --- | --------- | ----------- |
| **JSON String** | Input | The JSON to parse. |
| **Field Name** | Input | The field to get. |
| **Out Value** | Output | The string value. |
| **Return Value** | Output | **true** if the field exists. |

```
JSON = {"name":"Bob","title":"Hero"}

Get String Field(JSON, "name")
→ Out Value: "Bob"
→ Return Value: true
```

Numbers and booleans are converted to text. Objects, arrays, and `null` give you an empty string.

## Get Number Field

Extracts numbers. Gets a numeric value from the JSON as a **Float**.

| Pin | Direction | Description |
| --- | --------- | ----------- |
| **JSON String** | Input | The JSON to parse. |
| **Field Name** | Input | The field to get. |
| **Out Value** | Output | The number as a float. |
| **Return Value** | Output | **true** if the field exists. |

```
JSON = {"health":100,"damage":25.5}

Get Number Field(JSON, "health")
→ Out Value: 100.0
→ Return Value: true
```

**Tips:**

* Handles both whole numbers and decimals. Convert to an integer in your Blueprint if you need one.
* **Return Value** only tells you the field exists. It doesn't check that the value is a number. Values that can't be converted come back as `0`.

## Get Boolean Field

Extracts true/false. Gets a boolean value from the JSON.

| Pin | Direction | Description |
| --- | --------- | ----------- |
| **JSON String** | Input | The JSON to parse. |
| **Field Name** | Input | The field to get. |
| **Out Value** | Output | The boolean value. |
| **Return Value** | Output | **true** if the field exists. |

```
JSON = {"alive":true,"flying":false}

Get Boolean Field(JSON, "alive")
→ Out Value: true
→ Return Value: true
```

## Get Array Field

Extracts lists. Gets an array from the JSON, with every element returned as a string.

| Pin | Direction | Description |
| --- | --------- | ----------- |
| **Array Type** | Input | **String Array**, **Number Array**, or **Object Array**. |
| **JSON String** | Input | The JSON to parse. |
| **Field Name** | Input | The field to get. |
| **Out Values** | Output | The array elements, as strings. |
| **Return Value** | Output | **true** if the field exists and is an array. |

```
// String array
JSON = {"items":["sword","shield","potion"]}
Get Array Field(String Array, JSON, "items")
→ Out Values: ["sword","shield","potion"]

// Number array (returned as strings)
JSON = {"scores":[100,200,25.5]}
Get Array Field(Number Array, JSON, "scores")
→ Out Values: ["100.0","200.0","25.5"]

// Object array
JSON = {"players":[{"name":"Alice"},{"name":"Bob"}]}
Get Array Field(Object Array, JSON, "players")
→ Out Values: ['{"name":"Alice"}','{"name":"Bob"}']
```

**Tips:**

* Numbers come back as strings, always with a decimal point. Convert them in your Blueprint with **String to Float**.
* Object arrays give you JSON strings that you can parse further with the other parsing nodes.
* In an **Object Array**, elements that aren't objects are skipped.
* Use a **For Each Loop** to process the items.

## Get Object Field

Extracts nested objects. Gets a nested JSON object as a string.

| Pin | Direction | Description |
| --- | --------- | ----------- |
| **JSON String** | Input | The JSON to parse. |
| **Field Name** | Input | The field to get. |
| **Out JSON** | Output | The nested object as a JSON string. |
| **Return Value** | Output | **true** if the field exists and is an object. |

```
JSON = {"player":{"name":"Bob","health":100}}

Get Object Field(JSON, "player")
→ Out JSON: {"name":"Bob","health":100}
→ Return Value: true

// Now parse the nested object
Get String Field(Out JSON, "name")
→ "Bob"
```

**Tips:**

* This is how you walk through nested structures.
* Chain **Get Object Field** calls for deeply nested data.

## Get All Field Names

What's in this box? Returns the names of every field in a JSON object.

| Pin | Direction | Description |
| --- | --------- | ----------- |
| **JSON String** | Input | The JSON to inspect. |
| **Out Field Names** | Output | The names of all top-level fields. |
| **Return Value** | Output | **true** if the JSON is valid. |

```
JSON = {"name":"Bob","age":25,"score":100}

Get All Field Names(JSON)
→ Out Field Names: ["name","age","score"]
→ Return Value: true
```

**Tips:**

* Use it with a **For Each Loop** to process JSON when you don't know its structure ahead of time.
* Field order isn't guaranteed.
* Great for debugging: print the names to see what's in your JSON.
