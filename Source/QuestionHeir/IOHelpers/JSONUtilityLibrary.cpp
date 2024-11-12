// Fill out your copyright notice in the Description page of Project Settings.


#include "JSONUtilityLibrary.h"
#include "JsonObjectConverter.h"
#include "DesktopPlatformModule.h"
#include "IDesktopPlatform.h"
#include "HAL/PlatformFilemanager.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"
#include "Framework/Application/SlateApplication.h"

void UJSONUtilityLibrary::SaveDataToJson(const TArray<FQuestionStruct>& Questions)
{
    FString SaveFilePath;

    // Create a desktop platform instance
    IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
    if (DesktopPlatform)
    {
        // Setup file types and dialog settings
        FString DefaultPath = FPaths::ProjectDir();
        FString FileTypes = TEXT("JSON files (*.json)|*.json");
        FString DefaultFileName = TEXT("Questions.json");

        // Open the file save dialog
        TArray<FString> OutFilenames;
        bool bFileSelected = DesktopPlatform->SaveFileDialog(
            FSlateApplication::Get().FindBestParentWindowHandleForDialogs(nullptr),
            TEXT("Save your questions as JSON"),
            DefaultPath,
            DefaultFileName,
            FileTypes,
            EFileDialogFlags::None,
            OutFilenames
        );

        if (bFileSelected && OutFilenames.Num() > 0)
        {
            SaveFilePath = OutFilenames[0];
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("File save operation canceled"));
            return; // Exit if no file was selected
        }
    }

    // Prepare the JSON array to hold each question as a JSON object
    TSharedPtr<FJsonObject> JsonRootObject = MakeShareable(new FJsonObject());
    TArray<TSharedPtr<FJsonValue>> JsonArray;

    for (const FQuestionStruct& Question : Questions)
    {
        FString QuestionJsonString = UJSONUtilityLibrary::ConvertStructToJson(Question);
        TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(QuestionJsonString);
        TSharedPtr<FJsonObject> JsonQuestionObject = MakeShareable(new FJsonObject());
        if (FJsonSerializer::Deserialize(JsonReader, JsonQuestionObject))
        {
            JsonArray.Add(MakeShareable(new FJsonValueObject(JsonQuestionObject)));
        }
    }

    JsonRootObject->SetArrayField(TEXT("Questions"), JsonArray);

    // Convert the root object to a JSON string
    FString JsonOutput;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonOutput);
    FJsonSerializer::Serialize(JsonRootObject.ToSharedRef(), Writer);

    // Save the JSON string to the selected file
    FFileHelper::SaveStringToFile(JsonOutput, *SaveFilePath);
}


FString UJSONUtilityLibrary::ConvertStructToJson(const FQuestionStruct& QuestionStruct)
{
	FString OutputString;
   
	if (FJsonObjectConverter::UStructToJsonObjectString(QuestionStruct, OutputString))
	{
		return OutputString; // Success: Returns the JSON string
	}

	return ""; // If conversion failed
}

void UJSONUtilityLibrary::SaveAnsweredDataToJson(const TArray<FAnsweredQuestionStruct>& AnsweredQuestion)
{
    FString SaveFilePath;

    // Create a desktop platform instance
    IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
    if (DesktopPlatform)
    {
        // Setup file types and dialog settings
        FString DefaultPath = FPaths::ProjectDir();
        FString FileTypes = TEXT("JSON files (*.json)|*.json");
        FString DefaultFileName = TEXT("Answered.json");

        // Open the file save dialog
        TArray<FString> OutFilenames;
        bool bFileSelected = DesktopPlatform->SaveFileDialog(
            FSlateApplication::Get().FindBestParentWindowHandleForDialogs(nullptr),
            TEXT("Save your answers as JSON"),
            DefaultPath,
            DefaultFileName,
            FileTypes,
            EFileDialogFlags::None,
            OutFilenames
        );

        if (bFileSelected && OutFilenames.Num() > 0)
        {
            SaveFilePath = OutFilenames[0];
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("File save operation canceled"));
            return; // Exit if no file was selected
        }
    }

    // Prepare the JSON array to hold each question as a JSON object
    TSharedPtr<FJsonObject> JsonRootObject = MakeShareable(new FJsonObject());
    TArray<TSharedPtr<FJsonValue>> JsonArray;

    for (const FAnsweredQuestionStruct& Answered : AnsweredQuestion)
    {
        FString AnsweredJsonString = UJSONUtilityLibrary::ConvertStructToJson(Answered);
        TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(AnsweredJsonString);
        TSharedPtr<FJsonObject> JsonAnsweredObject = MakeShareable(new FJsonObject());
        if (FJsonSerializer::Deserialize(JsonReader, JsonAnsweredObject))
        {
            JsonArray.Add(MakeShareable(new FJsonValueObject(JsonAnsweredObject)));
        }
    }

    JsonRootObject->SetArrayField(TEXT("Answers"), JsonArray);

    // Convert the root object to a JSON string
    FString JsonOutput;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonOutput);
    FJsonSerializer::Serialize(JsonRootObject.ToSharedRef(), Writer);

    // Save the JSON string to the selected file
    FFileHelper::SaveStringToFile(JsonOutput, *SaveFilePath);
}

FString UJSONUtilityLibrary::ConvertStructToJson(const FAnsweredQuestionStruct& AnsweredQuestionStruct)
{
    FString OutputString;
   
    if (FJsonObjectConverter::UStructToJsonObjectString(AnsweredQuestionStruct, OutputString))
    {
        return OutputString; // Success: Returns the JSON string
    }

    return ""; // If conversion failed
}

TArray<FQuestionStruct> UJSONUtilityLibrary::GetDataFromJson()
{
    TArray<FQuestionStruct> QuestionArray;

    // Create a desktop platform instance
    IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
    if (DesktopPlatform)
    {
        FString DefaultPath = FPaths::ProjectDir();
        FString FileTypes = TEXT("JSON files (*.json)|*.json");
        FString DefaultFileName = TEXT("Questions.json");

        // Open the file open dialog
        TArray<FString> OutFilenames;
        bool bFileSelected = DesktopPlatform->OpenFileDialog(
            FSlateApplication::Get().FindBestParentWindowHandleForDialogs(nullptr),
            TEXT("Open your questions JSON file"),
            DefaultPath,
            DefaultFileName,
            FileTypes,
            EFileDialogFlags::None,
            OutFilenames
        );

        if (bFileSelected && OutFilenames.Num() > 0)
        {
            FString FilePath = OutFilenames[0];
            FString FileContent;

            if (FFileHelper::LoadFileToString(FileContent, *FilePath))
            {
                TSharedPtr<FJsonObject> JsonObject;
                TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(FileContent);
                if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
                {
                    // Initialize the pointer to nullptr
                    const TArray<TSharedPtr<FJsonValue>>* JsonArrayPtr = nullptr;

                    // Try to get the array field
                    if (JsonObject.IsValid() && JsonObject->TryGetArrayField(TEXT("Questions"), JsonArrayPtr))
                    {
                        // Check if the pointer is valid before using it
                        if (JsonArrayPtr)
                        {
                            for (const TSharedPtr<FJsonValue>& JsonValue : *JsonArrayPtr)
                            {
                                if (JsonValue.IsValid() && JsonValue->Type == EJson::Object)
                                {
                                    TSharedPtr<FJsonObject> JsonQuestionObject = JsonValue->AsObject();
                                    if (JsonQuestionObject.IsValid())
                                    {
                                        FQuestionStruct QuestionStruct;
                                        if (FJsonObjectConverter::JsonObjectToUStruct(JsonQuestionObject.ToSharedRef(), &QuestionStruct, 0, 0))
                                        {
                                            QuestionArray.Add(QuestionStruct);
                                        }
                                        else
                                        {
                                            UE_LOG(LogTemp, Warning, TEXT("Failed to convert JSON to FQuestionStruct for value: %s"), *JsonValue->AsString());
                                        }
                                    }
                                }
                            }
                        }
                        else
                        {
                            UE_LOG(LogTemp, Error, TEXT("JsonArrayPtr is null after trying to get the Questions array"));
                        }
                    }
                    else
                    {
                        UE_LOG(LogTemp, Error, TEXT("Failed to get 'Questions' array from JSON object"));
                    }
                }
                else
                {
                    UE_LOG(LogTemp, Error, TEXT("Failed to deserialize JSON: %s"), *FileContent);
                }
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("Failed to load file content from: %s"), *FilePath);
            }
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("File open operation canceled or no file selected"));
        }
    }
    UE_LOG(LogTemp, Error, TEXT("Questions Loaded Successfully!"));
    return QuestionArray;
}
