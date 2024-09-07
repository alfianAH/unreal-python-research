import unreal
import re
import argparse


def get_selected_folders():
    folder_path_list: list[str] = unreal.EditorUtilityLibrary.get_selected_folder_paths()

    adjusted_folders = []

    for folder in folder_path_list:
        if folder.startswith("/All/"):
            adjusted_folder = folder.replace("/All", "")
            adjusted_folders.append(adjusted_folder)
        else:
            adjusted_folders.append(folder)

    return adjusted_folders


def generate_formatted_name_for_asset(asset):
    rename_config = {
        "prefixes_per_type": [
            {"type": unreal.MaterialInstance, "prefix": "MI_"},
            {"type": unreal.Material, "prefix": "M_"},
            {"type": unreal.Texture, "prefix": "T_"},
            {"type": unreal.NiagaraSystem, "prefix": "NS_"},
            {"type": unreal.Blueprint, "prefix": "BP_"}
        ]
    }

    name = asset.get_name()
    
    for i in range (len(rename_config["prefixes_per_type"])):
        prefix_config = rename_config["prefixes_per_type"][i]

        prefix = prefix_config["prefix"]
        asset_type = prefix_config["type"]

        if isinstance(asset, asset_type) and not name.startswith(prefix):
            return prefix + name

    # Type not important for us
    return name


def generate_unformatted_name_for_asset(old_name):
    match = re.search(r'[\w]+_(\w+)', old_name)

    if match is not None and match.group() is not None:
        group_result = match.group(1)
        return group_result
    else:
        return None
    

def batch_rename(folder_paths, is_rollback=False):
    asset_registry = unreal.AssetRegistryHelpers.get_asset_registry()
    
    for folder_path in folder_paths:
        if not asset_registry.has_assets(folder_path, recursive=True): 
            continue
        
        assets_in_folder: list[unreal.AssetData] = asset_registry.get_assets_by_path(folder_path, recursive=True)

        for asset_data in assets_in_folder:
            asset = asset_data.get_asset()
            old_name = asset.get_name()
            asset_old_path = asset.get_path_name()
            asset_folder = unreal.Paths.get_path(asset_old_path)

            if is_rollback:
                new_name = generate_unformatted_name_for_asset(old_name)
                
                if new_name is None:
                    continue
            else:
                new_name = generate_formatted_name_for_asset(asset)
            
            new_path = f"{asset_folder}/{new_name}" 
            is_rename_success = unreal.EditorAssetLibrary.rename_asset(asset_old_path, new_path)

            unreal.log(f"Processing {asset_old_path}")

            if not is_rename_success:
                unreal.log_warning(f"Could not rename: {asset_old_path}")
            else:
                unreal.log(f"Rename {old_name} to {new_name}")


def parse_arguments():
    parser = argparse.ArgumentParser(description="Process some arguments.")
    
    # Add a boolean argument
    parser.add_argument(
        'boolean_arg', 
        type=str,  # We'll convert this later
        help='A boolean argument (True or False)'
    )
    
    args = parser.parse_args()
    return args


def __main__():
    folder_paths = get_selected_folders()
    args = parse_arguments()
    is_rollback = args.boolean_arg.lower() in ['true', '1', 't', 'y', 'yes']
    batch_rename(folder_paths, is_rollback)


if __name__ == "__main__":
    __main__()