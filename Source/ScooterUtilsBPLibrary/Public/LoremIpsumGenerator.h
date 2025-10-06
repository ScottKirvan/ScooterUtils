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
    // Generate lorem ipsum text with specified parameters
    UFUNCTION(BlueprintCallable, Category = "Scooter Utilities|Lorem Ipsum")
    static FString GenerateLoremIpsum(int32 NumParagraphs = 3, int32 MinSentencesPerParagraph = 4, int32 MaxSentencesPerParagraph = 8);

    // Generate a specific number of sentences
    UFUNCTION(BlueprintCallable, Category = "Scooter Utilities|Lorem Ipsum")
    static FString GenerateSentences(int32 NumSentences);

    // Generate a specific number of words
    UFUNCTION(BlueprintCallable, Category = "Scooter Utilities|Lorem Ipsum")
    static FString GenerateWords(int32 NumWords);

private:
    static TArray<FString> GetLoremWords();
    static FString GenerateSentence(int32 MinWords = 8, int32 MaxWords = 16);
};