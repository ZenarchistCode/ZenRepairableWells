modded class ActionConstructor
{
    override void RegisterActions(TTypenameArray actions)
    {
        super.RegisterActions(actions);

        //! REPAIR WELLS 
        actions.Insert(ActionZenRepairWell);
    }
}