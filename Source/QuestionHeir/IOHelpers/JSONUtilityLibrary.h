// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "JSONUtilityLibrary.generated.h"

USTRUCT(BlueprintType)
struct FAnswerStruct
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Answer")
	FText Answer;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="AnswerCorrectBool")
	bool IsCorrect;
	
};

USTRUCT(BlueprintType)
struct FQuestionStruct
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Question")
	FText QuestionText;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Question")
	TArray<FAnswerStruct> Answers;
	
};

USTRUCT(BlueprintType)
struct FAnsweredQuestionStruct
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="AnsweredQuestion")
	FText QuestionText;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="AnsweredQuestion")
	FText Answer;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="AnsweredQuestion")
	float TimeTakenToAnswer;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="AnsweredQuestion")
	int IncorrectAttempts;
};

/**
 * 
 */
UCLASS()
class QUESTIONHEIR_API UJSONUtilityLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category="JSON")
	static void SaveDataToJson(const TArray<FQuestionStruct>& Questions);
	static FString ConvertStructToJson(const FQuestionStruct& QuestionStruct);

	UFUNCTION(BlueprintCallable, Category="JSON")
	static void SaveAnsweredDataToJson(const TArray<FAnsweredQuestionStruct>& AnsweredQuestion);
	static FString ConvertStructToJson(const FAnsweredQuestionStruct& AnsweredQuestionStruct);

	//Read the Json file and return an array of QuestionStructs
	UFUNCTION(BlueprintCallable, Category="JSON")
	static TArray<FQuestionStruct> GetDataFromJson();
};
