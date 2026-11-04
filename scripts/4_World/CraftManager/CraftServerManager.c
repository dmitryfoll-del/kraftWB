class CraftServerManager
{
    const private static string m_ProfilePath = "$profile:";
    const private static string m_FolderName = "HP";
    const private static string m_FileName = "HP_Crafter";

    ref CraftClasses m_CraftClasses;

    void CraftServerManager()
    {
        m_CraftClasses = new CraftClasses();
    }

    static CraftServerManager LoadData()
    {
        CraftServerManager traderData = new CraftServerManager();
        string directory = m_ProfilePath + m_FolderName;
        string path = directory + "/" + m_FileName + ".json";

        if (!FileExist(directory))
        {
            MakeDirectory(directory);
        }

        if (!FileExist(path))
        {
            traderData.CreateDefaultConfig();
            JsonFileLoader<CraftServerManager>.JsonSaveFile(path, traderData);
            Print("[HP_Crafter] Создан конфиг: " + path);
        }

        JsonFileLoader<CraftServerManager>.JsonLoadFile(path, traderData);
        return traderData;
    }

    protected void CreateDefaultConfig()
    {
        CraftCategory category;
        CraftItem recipe;

        // Категория: Выживание
        category = new CraftCategory();
        category.CategoryName = "Выживание";

        recipe = new CraftItem();
        recipe.Result = "Rope";
        recipe.ResultCount = 1;
        recipe.ComponentsDontAffectHealth = 1;
        recipe.CraftType = "craftpic";
        recipe.RecipeName = "Верёвка";
        AddComponent(recipe, "Rag", 6);
        category.CraftItems.Insert(recipe);

        recipe = new CraftItem();
        recipe.Result = "Torch";
        recipe.ResultCount = 1;
        recipe.ComponentsDontAffectHealth = 1;
        recipe.CraftType = "craftpic";
        recipe.RecipeName = "Факел";
        AddComponent(recipe, "LongWoodenStick", 1);
        AddComponent(recipe, "Rag", 1);
        category.CraftItems.Insert(recipe);

        m_CraftClasses.CraftCategories.Insert(category);

        // Категория: Медицина
        category = new CraftCategory();
        category.CategoryName = "Медицина";

        recipe = new CraftItem();
        recipe.Result = "BandageDressing";
        recipe.ResultCount = 1;
        recipe.ComponentsDontAffectHealth = 1;
        recipe.CraftType = "medicpic";
        recipe.RecipeName = "Бинт";
        AddComponent(recipe, "Rag", 2);
        category.CraftItems.Insert(recipe);

        recipe = new CraftItem();
        recipe.Result = "Splint";
        recipe.ResultCount = 1;
        recipe.ComponentsDontAffectHealth = 1;
        recipe.CraftType = "medicpic";
        recipe.RecipeName = "Шина";
        AddComponent(recipe, "LongWoodenStick", 1);
        AddComponent(recipe, "Rag", 1);
        category.CraftItems.Insert(recipe);

        m_CraftClasses.CraftCategories.Insert(category);

        // Категория: Инструменты
        category = new CraftCategory();
        category.CategoryName = "Инструменты";

        recipe = new CraftItem();
        recipe.Result = "StoneKnife";
        recipe.ResultCount = 1;
        recipe.ComponentsDontAffectHealth = 1;
        recipe.CraftType = "toolspic";
        recipe.RecipeName = "Каменный нож";
        AddComponent(recipe, "SmallStone", 2);
        category.CraftItems.Insert(recipe);

        recipe = new CraftItem();
        recipe.Result = "ImprovisedFishingRod";
        recipe.ResultCount = 1;
        recipe.ComponentsDontAffectHealth = 1;
        recipe.CraftType = "toolspic";
        recipe.RecipeName = "Самодельная удочка";
        AddComponent(recipe, "LongWoodenStick", 1);
        AddComponent(recipe, "Rope", 1);
        category.CraftItems.Insert(recipe);

        m_CraftClasses.CraftCategories.Insert(category);
    }

    protected void AddComponent(CraftItem recipe, string classname, int amount)
    {
        CraftComponent component = new CraftComponent();
        component.Classname = classname;
        component.Amount = amount;
        component.Destroy = true;
        component.Changehealth = 0.0;
        recipe.CraftComponents.Insert(component);
    }

    void SendTraderData(PlayerBase player)
    {
        player.RPCSingleParam(HPCc.SERVER_SEND_MAIN_DATA, new Param1<ref CraftClasses>(m_CraftClasses), true, player.GetIdentity());
    }
}

ref CraftServerManager g_CraftServerManager;
