﻿using Windows.Storage;
using Manager.Attributes;

namespace Manager;

[LoadSaveConfiguration<AppConfig>(nameof(_configurationContainer), CastMethod = "Manager.Services.ExtensionMethods.Misc.CastThrow")]
public static partial class AppContext
{
    private static ApplicationDataContainer _configurationContainer = null!;

    private const string ConfigurationContainerKey = "Config";
    public static string AppLocalFolder { get; private set; } = null!;

    public static void Initialize()
    {
        AppLocalFolder = ApplicationData.Current.LocalFolder.Path;
        if (!ApplicationData.Current.RoamingSettings.Containers.ContainsKey(ConfigurationContainerKey))
            _ = ApplicationData.Current.RoamingSettings.CreateContainer(ConfigurationContainerKey, ApplicationDataCreateDisposition.Always);

        _configurationContainer = ApplicationData.Current.RoamingSettings.Containers[ConfigurationContainerKey];
    }

    public static int ChangeTheme
    {
        set => _configurationContainer.Values[nameof(AppConfig.Theme)] = value;
    }
}