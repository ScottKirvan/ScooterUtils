# Lorem Ipsum C++ Reference

Generate placeholder text from C++ with `ULoremIpsumGenerator`.

**Header:** `LoremIpsumGenerator.h` · **Class:** `ULoremIpsumGenerator`

The text is randomized on every call. For how sentences are built, see the [Lorem Ipsum nodes](../blueprint-nodes/lorem-ipsum).

## Function Reference

| Name | Returns | Description |
| ---- | ------- | ----------- |
| `GenerateLoremIpsum(int32 NumParagraphs = 3, int32 MinSentencesPerParagraph = 4, int32 MaxSentencesPerParagraph = 8)` | `FString` | Paragraphs of text, each with a random number of sentences between the minimum and maximum. Paragraphs are separated by a blank line (`\n\n`). |
| `GenerateSentences(int32 NumSentences)` | `FString` | The given number of sentences, separated by spaces. |
| `GenerateWords(int32 NumWords)` | `FString` | The given number of lowercase words, separated by spaces, with no punctuation. |

All of them are `static`. Passing `0` for the count returns an empty string.

## Example

```cpp
#include "LoremIpsumGenerator.h"

const FText Title = FText::FromString(ULoremIpsumGenerator::GenerateWords(3));
const FText Body = FText::FromString(ULoremIpsumGenerator::GenerateLoremIpsum(2));
const FString Dialogue = ULoremIpsumGenerator::GenerateSentences(1);
```
