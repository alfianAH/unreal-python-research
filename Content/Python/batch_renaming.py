import unreal


def generate_new_name_for_asset(asset):
    rename_config = {
        "prefixes_per_type": [
            {"type": unreal.MaterialInstance, "prefix": "MI_"},
            {"type": unreal.Material, "prefix": "M_"},
            {"type": unreal.Texture, "prefix": "T_"},
            {"type": unreal.NiagaraSystem, "prefix": "NS_"},
        ]
    }

    name = asset.get_name()
    print(f"Asset {name} is a {type(asset)}")
    
    for i in range (len(rename_config["prefixes_per_type"])):
        prefix_config = rename_config["prefixes_per_type"][i]

        prefix = prefix_config["prefix"]
        asset_type = prefix_config["type"]

        if isinstance(asset, asset_type) and not name.startswith(prefix):
            return prefix + name

    # Type not important for us
    return name


def get_selected_content_browser_assets():
    editor_utility = unreal.EditorUtilityLibrary()
    selected_assets = editor_utility.get_selected_assets()

    return selected_assets


def batch_rename():
    selected_assets = get_selected_content_browser_assets()
    for asset in selected_assets:
        old_name = asset.get_name()
        asset_old_path = asset.get_path_name()
        asset_folder = unreal.Paths.get_path(asset_old_path)

        new_name = generate_new_name_for_asset(asset)
        new_path = f"{asset_folder}/{new_name}"

        is_rename_success = unreal.EditorAssetLibrary.rename_asset(asset_old_path, new_path)

        print(f"Renaming {old_name} to {new_name}...")
        if not is_rename_success:
            unreal.log_error(f"Could not rename: {asset_old_path}")


def __main__():
    batch_rename()
    


if __name__ == "__main__":
    __main__()
