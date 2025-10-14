# JSON Blueprint Library - User Guide

Welcome to the **JSON Blueprint Library**! This is your one-stop shop for creating, parsing, and manipulating JSON data right in your Unreal Engine blueprints. No more wrestling with complex JSON structures or wishing you could just save some data to a file. We've got you covered! 🎉

## Table of Contents

- [What's This All About?](#whats-this-all-about)
- [The Quick Start](#the-quick-start)
- [📝 Creation Nodes](#-creation-nodes)
  - [Add Field](#add-field)
  - [Add Array Field](#add-array-field)
  - [Add Object Field](#add-object-field)
  - [Add Null Field](#add-null-field)
  - [Remove Field](#remove-field)
  - [Merge JSON](#merge-json)
  - [Pretty Print JSON](#pretty-print-json)
  - [Minify JSON](#minify-json)
- [🔍 Parsing Nodes](#-parsing-nodes)
  - [Is Valid JSON](#is-valid-json)
  - [Has Field](#has-field)
  - [Is Field Null](#is-field-null)
  - [Get String Field](#get-string-field)
  - [Get Number Field](#get-number-field)
  - [Get Boolean Field](#get-boolean-field)
  - [Get Array Field](#get-array-field)
  - [Get Object Field](#get-object-field)
  - [Get All Field Names](#get-all-field-names)
- [🎯 Real-World Examples](#-real-world-examples)
- [🎓 Tips & Best Practices](#-tips--best-practices)
- [🐛 Troubleshooting](#-troubleshooting)
- [🚀 Advanced: C++ Integration](#-advanced-c-integration)
- [📚 JSON Quick Reference](#-json-quick-reference)

---

## What's This All About?

JSON (JavaScript Object Notation) is basically the universal language for storing and transmitting data. Think of it as a super-organized notebook where you can write down anything: numbers, text, lists, even nested structures. This library gives you simple blueprint nodes to work with JSON without needing to know any C++ or complicated APIs.

**What can you do with it?**
- 💾 Save game data (player stats, inventory, settings)
- 🌐 Communicate with web APIs
- 📝 Store configuration files
- 🔄 Exchange data between systems
- 🗂️ Create structured save files that are human-readable

---

## The Quick Start

Here's the simplest possible example - creating a JSON object with a player name:

```
1. Use "Add Field" node
2. Set Field Type: String
3. Set JSONString: "" (empty string)
4. Set FieldName: "PlayerName"
5. Set Value: "SuperGamer123"
6. Result: {"PlayerName":"SuperGamer123"}
```

That's it! You just made JSON. Now let's dive deeper.

---

## 📝 Creation Nodes

These nodes build JSON from scratch. Chain them together to create complex structures!

### Add Field
**The Swiss Army Knife of JSON Creation**

This is your main workhorse. It adds a field to your JSON with a type you choose from a dropdown.

**Parameters:**
- **Field Type** (dropdown): String, Number, or Boolean
- **JSON String**: The existing JSON (use empty string `""` to start fresh)
- **Field Name**: What to call this field (e.g., "health", "score", "name")
- **Value**: The value as a string (we'll convert it based on type)

**Output:**
- **JSON String Out**: Your updated JSON

**Examples:**

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

// Chaining them together!
"" → Add Field(String, -, "name", "Bob")
   → Add Field(Number, -, "health", "100")
   → Add Field(Boolean, -, "alive", "true")
→ {"name":"Bob","health":100,"alive":true}
```

**💡 Pro Tips:**
- Numbers: If you pass "hello" when type is Number, you'll get 0 (garbage in, zero out!)
- Booleans: Accepts "true"/"false", "1"/"0", or anything really (non-zero = true)
- Empty string: Starting with `""` creates a brand new JSON object

---

### Add Array Field
**For When You Need a List**

Arrays are just lists of things. This node lets you add arrays of strings, numbers, or even entire JSON objects!

**Parameters:**
- **Array Type** (dropdown): String Array, Number Array, or Object Array
- **JSON String**: The existing JSON
- **Field Name**: Name for this array
- **Values**: Array of strings (we convert based on type)

**Output:**
- **JSON String Out**: Updated JSON with your array

**Examples:**

```
// String array (player inventory items)
Add Array Field(String Array, "", "inventory", ["sword", "potion", "shield"])
→ {"inventory":["sword","potion","shield"]}

// Number array (high scores)
Add Array Field(Number Array, "", "scores", ["100", "250", "175"])
→ {"scores":[100,250,175]}

// Object array (list of players)
Player1 = {"name":"Alice","score":"100"}
Player2 = {"name":"Bob","score":"200"}
Add Array Field(Object Array, "", "players", [Player1, Player2])
→ {"players":[{"name":"Alice","score":100},{"name":"Bob","score":200}]}
```

**💡 Pro Tips:**
- Object arrays are SUPER useful for lists of enemies, items, players, etc.
- Remember: everything goes in as strings, we convert them for you
- Empty arrays are totally fine: `[]`

---

### Add Object Field
**Nesting Dolls, JSON Edition**

Want to put a JSON object inside another JSON object? This is your node. Great for grouping related data.

**Parameters:**
- **JSON String**: The parent JSON
- **Field Name**: Name for the nested object
- **Nested JSON**: The JSON object to nest inside

**Output:**
- **JSON String Out**: JSON with nested object inside

**Example:**

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

**💡 Pro Tips:**
- Build the inner objects first, then nest them
- You can nest as deep as you want (but maybe don't go crazy)
- Perfect for Vectors, Rotators, or any grouped data

---

### Add Null Field
**Sometimes Nothing is Something**

Adds a field with a `null` value. Useful when you want to explicitly say "this field exists but has no value."

**Parameters:**
- **JSON String**: Existing JSON
- **Field Name**: Name for the null field

**Output:**
- **JSON String Out**: Updated JSON

**Example:**

```
Add Null Field("", "middleName")
→ {"middleName":null}
```

**💡 Pro Tips:**
- Null is different from empty string "" or zero
- Use it when a value is optional but you want to track it exists
- Check with `Is Field Null` later

---

### Remove Field
**The Eraser**

Removes a field from JSON. Now tells you if it actually found and removed something!

**Parameters:**
- **JSON String**: The JSON to modify
- **Field Name**: Field to remove

**Outputs:**
- **JSON String Out**: JSON with field removed
- **Success**: True if field existed and was removed

**Example:**

```
JSON = {"name":"Bob","age":25,"temp":99}
Remove Field(JSON, "temp") 
→ {"name":"Bob","age":25}
→ Success: true
```

---

### Merge JSON
**Smoosh Two JSONs Together**

Takes two JSON objects and combines them. Fields from the second JSON overwrite any duplicates in the first.

**Parameters:**
- **JSON String 1**: The base JSON
- **JSON String 2**: JSON to merge in

**Output:**
- **JSON String Out**: Combined JSON

**Example:**

```
JSON1 = {"name":"Bob","age":25}
JSON2 = {"age":26,"score":100}

Merge JSON(JSON1, JSON2)
→ {"name":"Bob","age":26,"score":100}
```

**💡 Pro Tips:**
- Second JSON wins on conflicts (age became 26)
- Great for applying updates or patches
- Doesn't merge nested objects (it replaces them)

---

### Pretty Print JSON
**Make It Look Nice**

Formats JSON with indentation and line breaks. Perfect for debugging or saving human-readable files.

**Parameters:**
- **JSON String**: The JSON to format

**Output:**
- **JSON String Out**: Beautifully formatted JSON

**Example:**

```
Before: {"name":"Bob","position":{"X":100,"Y":200}}

After:
{
  "name": "Bob",
  "position": {
    "X": 100,
    "Y": 200
  }
}
```

**💡 Pro Tips:**
- Use this before saving to files for debugging
- Great for config files humans need to edit
- Doesn't change the data, just the formatting

---

### Minify JSON
**Strip All The Whitespace**

Removes all formatting, indentation, and whitespace from JSON. Makes it compact for storage or transmission.

**Parameters:**
- **JSON String**: The JSON to minify

**Output:**
- **JSON String Out**: Compacted JSON with no whitespace

**Example:**

```
Before:
{
  "name": "Bob",
  "position": {
    "X": 100,
    "Y": 200
  }
}

After: {"name":"Bob","position":{"X":100,"Y":200}}
```

**💡 Pro Tips:**
- Use this before saving to disk to reduce file size
- Perfect for network transmission where size matters
- Opposite of Pretty Print JSON
- The data is identical, just the formatting changes

---

## 🔍 Parsing Nodes

These nodes read and extract data from JSON strings.

### Is Valid JSON
**The Gatekeeper**

Checks if a string is valid JSON before you try to parse it.

**Parameters:**
- **JSON String**: String to validate

**Output:**
- **Return Value**: True if valid JSON

**Example:**

```
Is Valid JSON('{"name":"Bob"}') → true
Is Valid JSON('not json at all') → false
Is Valid JSON('{"broken":}')     → false
```

**💡 Pro Tips:**
- ALWAYS check before parsing if the JSON came from external sources
- Prevents crashes from malformed data
- Returns false for empty strings

---

### Has Field
**Does This Field Exist?**

Checks if a specific field exists in the JSON.

**Parameters:**
- **JSON String**: The JSON to check
- **Field Name**: Field to look for

**Output:**
- **Return Value**: True if field exists

**Example:**

```
JSON = {"name":"Bob","age":25}

Has Field(JSON, "name") → true
Has Field(JSON, "email") → false
```

**💡 Pro Tips:**
- Check this before using Get nodes to avoid errors
- Works for any field type
- Returns false if JSON is invalid

---

### Is Field Null
**Is This Field Intentionally Empty?**

Checks if a field exists AND has a null value.

**Parameters:**
- **JSON String**: The JSON to check
- **Field Name**: Field to check

**Output:**
- **Return Value**: True if field is null

**Example:**

```
JSON = {"name":"Bob","email":null}

Is Field Null(JSON, "email") → true
Is Field Null(JSON, "name")  → false
Is Field Null(JSON, "missing") → false (doesn't exist)
```

---

### Get String Field
**Extract Text**

Gets a string value from JSON.

**Parameters:**
- **JSON String**: The JSON to parse
- **Field Name**: Field to get

**Outputs:**
- **Out Value**: The string value
- **Return Value**: True if successful

**Example:**

```
JSON = {"name":"Bob","title":"Hero"}

Get String Field(JSON, "name")
→ Out Value: "Bob"
→ Return: true
```

---

### Get Number Field
**Extract Numbers**

Gets a numeric value from JSON (returns as float).

**Parameters:**
- **JSON String**: The JSON to parse
- **Field Name**: Field to get

**Outputs:**
- **Out Value**: The number as float
- **Return Value**: True if successful

**Example:**

```
JSON = {"health":100,"damage":25.5}

Get Number Field(JSON, "health")
→ Out Value: 100.0
→ Return: true
```

**💡 Pro Tips:**
- Returns float, convert to int in blueprint if needed
- Handles both integers and decimals
- Returns false if field isn't a number

---

### Get Boolean Field
**Extract True/False**

Gets a boolean value from JSON.

**Parameters:**
- **JSON String**: The JSON to parse
- **Field Name**: Field to get

**Outputs:**
- **Out Value**: The boolean value
- **Return Value**: True if successful

**Example:**

```
JSON = {"alive":true,"flying":false}

Get Boolean Field(JSON, "alive")
→ Out Value: true
→ Return: true
```

---

### Get Array Field
**Extract Lists**

Gets an array from JSON. Returns everything as strings (convert numbers if needed).

**Parameters:**
- **Array Type** (dropdown): String Array, Number Array, or Object Array
- **JSON String**: The JSON to parse
- **Field Name**: Field to get
- **Out Values**: Array of strings

**Output:**
- **Return Value**: True if successful

**Examples:**

```
// String array
JSON = {"items":["sword","shield","potion"]}
Get Array Field(String Array, JSON, "items")
→ Out Values: ["sword","shield","potion"]

// Number array (returned as strings!)
JSON = {"scores":[100,200,300]}
Get Array Field(Number Array, JSON, "scores")
→ Out Values: ["100","200","300"]

// Object array
JSON = {"players":[{"name":"Alice"},{"name":"Bob"}]}
Get Array Field(Object Array, JSON, "players")
→ Out Values: ['{"name":"Alice"}','{"name":"Bob"}']
```

**💡 Pro Tips:**
- Numbers come back as strings - convert them in blueprint
- Object arrays give you JSON strings you can parse further
- Use ForEach loop to process array items

---

### Get Object Field
**Extract Nested Objects**

Gets a nested JSON object as a string.

**Parameters:**
- **JSON String**: The JSON to parse
- **Field Name**: Field to get

**Outputs:**
- **Out JSON**: The nested JSON as string
- **Return Value**: True if successful

**Example:**

```
JSON = {"player":{"name":"Bob","health":100}}

Get Object Field(JSON, "player")
→ Out JSON: {"name":"Bob","health":100}
→ Return: true

// Now parse the nested object
Get String Field(Out JSON, "name")
→ "Bob"
```

**💡 Pro Tips:**
- This is how you traverse nested structures
- Chain Get Object Field calls for deep nesting
- Remember: JSON is just strings, so you can parse the result

---

### Get All Field Names
**What's In This Box?**

Returns an array of all field names in a JSON object. Great for debugging or dynamic processing.

**Parameters:**
- **JSON String**: The JSON to inspect

**Outputs:**
- **Out Field Names**: Array of field names
- **Return Value**: True if successful

**Example:**

```
JSON = {"name":"Bob","age":25,"score":100}

Get All Field Names(JSON)
→ Out Field Names: ["name","age","score"]
→ Return: true
```

**💡 Pro Tips:**
- Use with ForEach to process unknown JSON structures
- Field order isn't guaranteed
- Great for debugging: print these to see what's in your JSON

---

## 🎯 Real-World Examples

### Example 1: Save Player Data

```
// Create player save data
SaveData = ""
  → Add Field(String, -, "playerName", PlayerName)
  → Add Field(Number, -, "level", LevelToString)
  → Add Field(Number, -, "health", HealthToString)
  → Add Field(Number, -, "maxHealth", MaxHealthToString)
  → Add Array Field(String Array, -, "inventory", InventoryItems)

// Save to file (use your file I/O system)
SaveStringToFile(SaveData, "save_slot_1.json")
```

### Example 2: Load Player Data

```
// Load from file
JSONString = LoadStringFromFile("save_slot_1.json")

// Validate and parse
if Is Valid JSON(JSONString):
    Get String Field(JSONString, "playerName") → PlayerName
    Get Number Field(JSONString, "level") → Level
    Get Number Field(JSONString, "health") → Health
    Get Array Field(String Array, JSONString, "inventory") → Inventory
```

### Example 3: Complex Nested Structure (Character Sheet)

```
// Build equipment
Weapon = ""
  → Add Field(String, -, "name", "Excalibur")
  → Add Field(Number, -, "damage", "50")
  → Add Field(String, -, "type", "Sword")

Armor = ""
  → Add Field(String, -, "name", "Plate Mail")
  → Add Field(Number, -, "defense", "30")

// Build character
Character = ""
  → Add Field(String, -, "name", "Sir Lancelot")
  → Add Field(Number, -, "level", "20")
  → Add Object Field(-, "weapon", Weapon)
  → Add Object Field(-, "armor", Armor)

Result:
{
  "name": "Sir Lancelot",
  "level": 20,
  "weapon": {
    "name": "Excalibur",
    "damage": 50,
    "type": "Sword"
  },
  "armor": {
    "name": "Plate Mail",
    "defense": 30
  }
}
```

### Example 4: Working with Arrays of Objects

```
// Create player entries
Player1 = "" 
  → Add Field(String, -, "name", "Alice")
  → Add Field(Number, -, "score", "100")

Player2 = ""
  → Add Field(String, -, "name", "Bob")
  → Add Field(Number, -, "score", "150")

// Create leaderboard
Leaderboard = ""
  → Add Array Field(Object Array, -, "players", [Player1, Player2])

// Later: Load and parse
Get Array Field(Object Array, Leaderboard, "players") → PlayerStrings

ForEach PlayerString in PlayerStrings:
    Get String Field(PlayerString, "name") → Name
    Get Number Field(PlayerString, "score") → Score
    Print: Name + " scored " + Score
```

---

## 🎓 Tips & Best Practices

### Always Validate External JSON
If JSON is coming from files, web APIs, or user input, ALWAYS check `Is Valid JSON` first!

### Use Pretty Print for Debugging
When things aren't working, use `Pretty Print JSON` and print it to screen. You'll instantly see what your data looks like.

### Start Simple, Then Nest
Build your JSON from the inside out. Create inner objects first, then nest them in outer objects.

### Remember: Everything is Strings
When creating JSON, all values go in as strings. The nodes convert them based on type. When reading arrays of numbers, remember they come back as strings!

### Check Field Existence
Before using Get nodes, consider using `Has Field` to check if the field exists. Prevents errors with malformed data.

### Chain Your Nodes
The output of one Add node feeds right into the next. This is the intended workflow - start with empty string `""`, then chain adds.

### File I/O is Separate
This library doesn't handle file operations. Use Unreal's file I/O nodes (or another plugin) to save/load the JSON strings to disk.

### Object Arrays Are Powerful
Don't forget about `Object Array` type! It's perfect for lists of complex items (inventory, enemies, quests, etc.)

---

## 🐛 Troubleshooting

**"My JSON looks weird!"**
- Use `Pretty Print JSON` and print it to see the structure
- Check for missing quotes around field names
- Make sure you're chaining the output correctly

**"Get Field returns false!"**
- Check if the field exists with `Has Field`
- Validate the JSON with `Is Valid JSON`
- Make sure field name matches exactly (case-sensitive!)

**"Numbers aren't working right!"**
- When reading number arrays, remember they return as strings
- When creating, make sure you're using Number type, not String
- Empty or invalid strings become 0

**"My nested objects are broken!"**
- Build inner objects completely before nesting
- Use `Get Object Field` to extract nested JSON
- Remember: you can parse the extracted object again

**"Array is empty!"**
- Check if you're using the right Array Type when reading
- Verify the array exists with `Has Field`
- Make sure the JSON is valid

---

## 🚀 Advanced: C++ Integration

For C++ developers, you can use the helper functions directly:

```cpp
#include "JSONBlueprintLibrary.h"

// These are free functions, not class members
TSharedPtr<FJsonObject> MyJson = ParseToJSONObject(JsonString);
FString OutputString = JSONObjectToString(MyJson);
```

The library uses Unreal's native `FJsonObject` under the hood, so you get full JSON functionality without any external dependencies.

---

## 📚 JSON Quick Reference

**Valid JSON Types:**
- `string`: Text in quotes `"hello"`
- `number`: Integers or floats `42` or `3.14`
- `boolean`: `true` or `false`
- `null`: Explicitly empty value
- `array`: List of values `[1,2,3]`
- `object`: Nested structure `{"key":"value"}`

**JSON Rules:**
- Field names must be in quotes
- String values must be in quotes
- Numbers and booleans are NOT in quotes
- Commas separate items (but not after the last one)
- Curly braces `{}` for objects, square brackets `[]` for arrays

---