ref ZenRepairableWellsConfig g_ZenWellsConfig;

static ZenRepairableWellsConfig GetZenWellsConfig()
{
	if (!g_ZenWellsConfig) GetZenConfigRegister().RegisterConfig(ZenRepairableWellsConfig);
	return g_ZenWellsConfig;
}

modded class ZenConfigRegister
{
	override void RegisterPreload()
	{
		super.RegisterPreload();
		RegisterType(ZenRepairableWellsConfig);
	}
}

class ZenRepairableWellsConfig: ZenConfigBase
{
	// -------------------------
	// CONFIG SETTINGS
	// -------------------------
	override void OnRegistered()
	{
		g_ZenWellsConfig = this;
	}
	
	override string    	GetCurrentVersion()   		{ return "1.29.1"; }
	override bool		ShouldLoadOnServer() 		{ return true; }
	override bool 		IsServerOnlyConfig()		{ return true; }
	
	override bool ReadJson(string path, out string err)
	{
		return JsonFileLoader<ZenRepairableWellsConfig>.LoadFile(path, this, err);
	}

	override bool WriteJson(string path, out string err)
	{
		return JsonFileLoader<ZenRepairableWellsConfig>.SaveFile(path, this, err);
	}

	// Main config data
	string MessageNotDrink;
	string MessageRepaired;
	bool DisableWellsByDefault;
	int DamageTool;
	int TimeToBreak;

	// Load config file or create default file if config doesn't exsit
	override void SetDefaults()
	{
		MessageNotDrink = "#zen_well_broken";
		MessageRepaired = "#zen_well_already_repaired";
		DisableWellsByDefault = true; // If true then all wells will be disabled by default. If false, only custom-added wells will be disabled.
		DamageTool = 50; // Damages pipe wrench
		TimeToBreak = 1209600; // How long the well stays working once repaired until it breaks again
	}
}