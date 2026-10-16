modded class PlayerBase
{
	bool IsAllowedZenWellUsage(ActionData action_data)
	{
		if (!action_data || !action_data.m_Target || !action_data.m_Target.GetObject() || !g_Game.IsDedicatedServer())
			return true;
		
		Well wellObj = null;

		if (action_data.m_Target.GetObject().IsInherited(Well))
		{
			wellObj = Well.Cast(action_data.m_Target.GetObject());
		}

		if (wellObj)
		{
			return wellObj.Zen_CanBeUsed(this);
		}
		
		return true;
	}
}