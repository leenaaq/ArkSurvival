#include "UISubsystem.h"
#include "../../UI/BaseWidget.h"
#include "Engine/World.h"
#include "Blueprint/UserWidget.h"

void UUISubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
}

void UUISubsystem::Deinitialize()
{
    CloseAllUI();
    CachedWidgets.Empty();
    Super::Deinitialize();
}

void UUISubsystem::OpenUI(const FString& UIName)
{
    if (!UIClasses.Contains(UIName))
    {
        return;
    }
    
    if (UIGroups.Contains(UIName))
    {
        CloseUIsByGroup(UIGroups[UIName]);
    }
    
    UBaseWidget* Widget = GetOrCreateWidget(UIName);
    if (Widget)
    {
        Widget->ShowWidget();
        ActiveUIStack.AddUnique(UIName);
    }
}

void UUISubsystem::CloseUI(const FString& UIName)
{
    if (CachedWidgets.Contains(UIName))
    {
        CachedWidgets[UIName]->HideWidget();
        ActiveUIStack.Remove(UIName);
        
        if (UICachePolicies.Contains(UIName) && 
            UICachePolicies[UIName] == EUICachePolicy::CacheTemporary)
        {
            CachedWidgets[UIName]->RemoveFromParent();
            CachedWidgets.Remove(UIName);
        }
    }
}

void UUISubsystem::ToggleUI(const FString& UIName)
{
    if (ActiveUIStack.Contains(UIName))
    {
        CloseUI(UIName);
    }
    else
    {
        OpenUI(UIName);
    }
}

void UUISubsystem::CloseAllUI()
{
    for (const FString& UIName : ActiveUIStack)
    {
        if (CachedWidgets.Contains(UIName))
        {
            CachedWidgets[UIName]->HideWidget();
        }
    }
    ActiveUIStack.Empty();
}

void UUISubsystem::CloseUIsByGroup(EUIGroup Group)
{
    TArray<FString> ToClose;
    
    for (const FString& UIName : ActiveUIStack)
    {
        if (UIGroups.Contains(UIName) && UIGroups[UIName] == Group)
        {
            ToClose.Add(UIName);
        }
    }
    
    for (const FString& UIName : ToClose)
    {
        CloseUI(UIName);
    }
}

UBaseWidget* UUISubsystem::GetOrCreateWidget(const FString& UIName)
{
    if (CachedWidgets.Contains(UIName))
    {
        return CachedWidgets[UIName];
    }
    
    if (UIClasses.Contains(UIName))
    {
        UWorld* World = GetWorld();
        if (World && World->GetFirstPlayerController())
        {
            UBaseWidget* NewWidget = CreateWidget<UBaseWidget>(
            GetWorld()->GetGameInstance(),
                UIClasses[UIName]
            );
            
            if (NewWidget)
            {
                if (UICachePolicies.Contains(UIName) && 
                    UICachePolicies[UIName] != EUICachePolicy::NeverCache)
                {
                    CachedWidgets.Add(UIName, NewWidget);
                }
                
                NewWidget->AddToViewport();
                NewWidget->HideWidget();
                return NewWidget;
            }
        }
    }
    
    return nullptr;
}

void UUISubsystem::CleanupTemporaryWidgets()
{
    // TODO 임시 캐시 위젯들의 시간 체크해서 정리
}

void UUISubsystem::RegisterUI(const FString& UIName, TSubclassOf<UBaseWidget> WidgetClass, EUIGroup Group, EUICachePolicy CachePolicy)
{
    UIClasses.Add(UIName, WidgetClass);
    UIGroups.Add(UIName, Group);
    UICachePolicies.Add(UIName, CachePolicy);
}