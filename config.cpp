class CfgPatches
{
	class ZenRepairableWells
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[] = 
		{ 
			"DZ_Data",
            "DZ_Scripts",
			"ZenModCore"
		};
	};
};

class CfgMods
{
	class ZenRepairableWells
	{
		author = "Zenarchist";
		type = "mod";
		storageVersion = 1; // CF storage
        dependencies[]=
		{
			"Game",
			"World",
			"Mission"
		};
		class defs
		{
			class gameScriptModule
            {
				value = "";
                files[]=
				{
					"ZenRepairableWells/scripts/3_game"
				};
            };
			
			class worldScriptModule
            {
                value="";
                files[]=
				{
					"ZenRepairableWells/scripts/4_world" 
				};
            };
			
	        class missionScriptModule
            {
                value="";
                files[]=
				{
					"ZenRepairableWells/scripts/5_mission" 
				};
            };
		}
	};
};