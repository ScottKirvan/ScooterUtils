// LoremIpsumGenerator.h
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LoremIpsumGenerator.generated.h"

UCLASS()
class ULoremIpsumGenerator : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
public:
    /**
     * Generates placeholder text in the Lorem Ipsum style, organized into paragraphs
     * 
     * @param NumParagraphs              Number of paragraphs to generate (default: 3)
     * @param MinSentencesPerParagraph   Minimum sentences in each paragraph (default: 4)
     * @param MaxSentencesPerParagraph   Maximum sentences in each paragraph (default: 8)
     * @return                           A string containing the generated Lorem Ipsum text with paragraphs separated by newlines
     * 
     * Example: Use this to create placeholder text for UI design, text blocks, or document templates
     */
    UFUNCTION(BlueprintCallable, Category = "Scooter Utilities|Lorem Ipsum",
              meta = (ToolTip = "Generates Lorem Ipsum placeholder text with customizable length",
                     Keywords = "lorem,ipsum,text,generate,placeholder,dummy,paragraph"))
    static FString GenerateLoremIpsum(int32 NumParagraphs = 3, int32 MinSentencesPerParagraph = 4, int32 MaxSentencesPerParagraph = 8);

    /**
     * Generates a specific number of Lorem Ipsum sentences
     * 
     * @param NumSentences    The number of sentences to generate
     * @return               A string containing the generated sentences with proper punctuation
     * 
     * Example: Use this when you need a specific amount of sentences, like for a character dialogue
     */
    UFUNCTION(BlueprintCallable, Category = "Scooter Utilities|Lorem Ipsum",
              meta = (ToolTip = "Generates a specific number of Lorem Ipsum sentences",
                     Keywords = "lorem,ipsum,text,generate,sentence,dialogue"))
    static FString GenerateSentences(int32 NumSentences);

    /**
     * Generates a specific number of Lorem Ipsum words
     * 
     * @param NumWords    The number of words to generate
     * @return           A space-separated string of random Lorem Ipsum words
     * 
     * Example: Use this for shorter placeholder text like button labels or short descriptions
     */
    UFUNCTION(BlueprintCallable, Category = "Scooter Utilities|Lorem Ipsum",
              meta = (ToolTip = "Generates a specific number of Lorem Ipsum words",
                     Keywords = "lorem,ipsum,text,generate,words,label"))
    static FString GenerateWords(int32 NumWords);

private:
    static TArray<FString> GetLoremWords();
    static FString GenerateSentence(int32 MinWords = 8, int32 MaxWords = 16);
};