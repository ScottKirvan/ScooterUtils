
// LoremIpsumGenerator.cpp
#include "LoremIpsumGenerator.h"

TArray<FString> ULoremIpsumGenerator::GetLoremWords()
{
    static TArray<FString> Words = {
        TEXT("lorem"), TEXT("ipsum"), TEXT("dolor"), TEXT("sit"), TEXT("amet"),
        TEXT("consectetur"), TEXT("adipiscing"), TEXT("elit"), TEXT("sed"), TEXT("do"),
        TEXT("eiusmod"), TEXT("tempor"), TEXT("incididunt"), TEXT("ut"), TEXT("labore"),
        TEXT("et"), TEXT("dolore"), TEXT("magna"), TEXT("aliqua"), TEXT("enim"),
        TEXT("ad"), TEXT("minim"), TEXT("veniam"), TEXT("quis"), TEXT("nostrud"),
        TEXT("exercitation"), TEXT("ullamco"), TEXT("laboris"), TEXT("nisi"), TEXT("aliquip"),
        TEXT("ex"), TEXT("ea"), TEXT("commodo"), TEXT("consequat"), TEXT("duis"),
        TEXT("aute"), TEXT("irure"), TEXT("in"), TEXT("reprehenderit"), TEXT("voluptate"),
        TEXT("velit"), TEXT("esse"), TEXT("cillum"), TEXT("fugiat"), TEXT("nulla"),
        TEXT("pariatur"), TEXT("excepteur"), TEXT("sint"), TEXT("occaecat"), TEXT("cupidatat"),
        TEXT("non"), TEXT("proident"), TEXT("sunt"), TEXT("culpa"), TEXT("qui"),
        TEXT("officia"), TEXT("deserunt"), TEXT("mollit"), TEXT("anim"), TEXT("id"),
        TEXT("est"), TEXT("laborum"), TEXT("vitae"), TEXT("suscipit"), TEXT("tellus"),
        TEXT("mauris"), TEXT("cursus"), TEXT("mattis"), TEXT("molestie"), TEXT("iaculis"),
        TEXT("at"), TEXT("erat"), TEXT("pellentesque"), TEXT("adipiscing"), TEXT("commodo"),
        TEXT("viverra"), TEXT("maecenas"), TEXT("accumsan"), TEXT("lacus"), TEXT("vel"),
        TEXT("facilisis"), TEXT("volutpat"), TEXT("morbi"), TEXT("tempus"), TEXT("iaculis"),
        TEXT("urna"), TEXT("condimentum"), TEXT("rhoncus"), TEXT("sem"), TEXT("quam"),
        TEXT("viverra"), TEXT("orci"), TEXT("sagittis"), TEXT("eu"), TEXT("volutpat"),
        TEXT("odio"), TEXT("facilisis"), TEXT("mauris"), TEXT("pharetra"), TEXT("massa")};
    return Words;
}

FString ULoremIpsumGenerator::GenerateSentence(int32 MinWords, int32 MaxWords)
{
    TArray<FString> Words = GetLoremWords();
    int32 NumWords = FMath::RandRange(MinWords, MaxWords);

    FString Sentence;
    for (int32 i = 0; i < NumWords; ++i)
    {
        int32 WordIndex = FMath::RandRange(0, Words.Num() - 1);
        FString Word = Words[WordIndex];

        // Capitalize first word
        if (i == 0)
        {
            Word = Word.Left(1).ToUpper() + Word.Mid(1);
        }

        Sentence += Word;

        // Add comma randomly
        if (i < NumWords - 1)
        {
            if (FMath::RandRange(0, 100) < 15) // 15% chance of comma
            {
                Sentence += TEXT(",");
            }
            Sentence += TEXT(" ");
        }
    }

    Sentence += TEXT(".");
    return Sentence;
}

FString ULoremIpsumGenerator::GenerateWords(int32 NumWords)
{
    TArray<FString> Words = GetLoremWords();
    FString Result;

    for (int32 i = 0; i < NumWords; ++i)
    {
        int32 WordIndex = FMath::RandRange(0, Words.Num() - 1);
        Result += Words[WordIndex];

        if (i < NumWords - 1)
        {
            Result += TEXT(" ");
        }
    }

    return Result;
}

FString ULoremIpsumGenerator::GenerateSentences(int32 NumSentences)
{
    FString Result;

    for (int32 i = 0; i < NumSentences; ++i)
    {
        Result += GenerateSentence();

        if (i < NumSentences - 1)
        {
            Result += TEXT(" ");
        }
    }

    return Result;
}

FString ULoremIpsumGenerator::GenerateLoremIpsum(int32 NumParagraphs, int32 MinSentencesPerParagraph, int32 MaxSentencesPerParagraph)
{
    FString Result;

    for (int32 p = 0; p < NumParagraphs; ++p)
    {
        int32 NumSentences = FMath::RandRange(MinSentencesPerParagraph, MaxSentencesPerParagraph);

        for (int32 s = 0; s < NumSentences; ++s)
        {
            Result += GenerateSentence();

            if (s < NumSentences - 1)
            {
                Result += TEXT(" ");
            }
        }

        // Add paragraph break (two newlines for markdown)
        if (p < NumParagraphs - 1)
        {
            Result += TEXT("\n\n");
        }
    }

    return Result;
}