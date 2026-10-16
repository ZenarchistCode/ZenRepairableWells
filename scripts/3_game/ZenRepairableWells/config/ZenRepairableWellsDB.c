ref ZenRepairableWellsDB g_ZenWellsDB;

static ZenRepairableWellsDB GetZenWellsDB()
{
	if (!g_ZenWellsDB) GetZenConfigRegister().RegisterConfig(ZenRepairableWellsDB);
	return g_ZenWellsDB;
}

modded class ZenConfigRegister
{
	override void RegisterPreload()
	{
		super.RegisterPreload();
		RegisterType(ZenRepairableWellsDB);
	}
}

class ZenRepairableWellsDB: ZenConfigBase
{
	// -------------------------
	// CONFIG SETTINGS
	// -------------------------
	override void OnRegistered()
	{
		g_ZenWellsDB = this;
	}
	
	override string 	GetRootFolder() 			{ return ZenConstants.GetDbFolder(); }
	override string    	GetCurrentVersion()   		{ return "1.29.1"; }
	override bool		ShouldLoadOnServer() 		{ return true; }
	override bool 		IsServerOnlyConfig()		{ return true; }
	
	override bool ReadJson(string path, out string err)
	{
		return JsonFileLoader<ZenRepairableWellsDB>.LoadFile(path, this, err);
	}

	override bool WriteJson(string path, out string err)
	{
		return JsonFileLoader<ZenRepairableWellsDB>.SaveFile(path, this, err);
	}

	// -------------------------
	// CONFIG VARS
	// -------------------------
	ref array<ref ZenRepairableWell> RepairableWells;

	// Load config file or create default file if config doesn't exsit
	override void SetDefaults()
	{
		RepairableWells = new array<ref ZenRepairableWell>;
	}

	// Get a repairable well index (if it exists) based on location
	int GetRepairableWellIndex(vector location)
	{
		for (int i = 0; i < RepairableWells.Count(); i++)
		{
			ZenRepairableWell well = RepairableWells.Get(i);

			float l1 = location[0];
			float l2 = location[1];
			float l3 = location[2];

			float w1 = well.Location[0];
			float w2 = well.Location[1];
			float w3 = well.Location[2];

			// Match location to config location with 1m tolerance (just to be safe considering json doesn't always save float values perfectly)
			if (l1 >= w1 - 1 && l1 <= w1 + 1 && l2 >= w2 - 1 && l2 <= w2 + 1 && l3 >= w3 - 1 && l3 <= w3 + 1)
			{
				return i;
			}
		}

		return -1;
	}

	// Save reparied well state to json config
	void SetWellRepaired(int index, vector location, bool repaired, bool forceSave)
	{
		int ts = CF_Date.Now().GetTimestamp() + GetZenWellsConfig().TimeToBreak;

		if (index < 0 || index > RepairableWells.Count())
		{
			ZenRepairableWell newWell = new ZenRepairableWell(location, true, ts);
			RepairableWells.Insert(newWell);
		}
		else
		{
			if (repaired)
			{
				RepairableWells.Get(index).Repaired = true;
				RepairableWells.Get(index).BreakTime = ts;
			}
			else
			{
				RepairableWells.Get(index).Repaired = false;
				RepairableWells.Get(index).BreakTime = 0;
			}
		}

		if (forceSave)
			Save(); // Save new well config.
	}
}

// Define repairable wells
class ZenRepairableWell
{
	vector Location;
	bool Invincible = false;
	bool Repaired = false;
	int BreakTime = 0;

	void ZenRepairableWell(vector loc, bool rep, int bt, bool inv = false)
	{
		Location = loc;
		Repaired = rep;
		BreakTime = bt;
		Invincible = inv;
	}
}