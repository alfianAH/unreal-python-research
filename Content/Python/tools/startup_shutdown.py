import unreal
from . import (
    menus,
    editor_tools
)
from .unreal_systems import asset_registry

# This module will make use of callbacks to handle two of its steps
# using a module variable cache we can prevent any duplicate work from happening
post_startup_id = None
shutdown_id = None


def run():
    """
    call this function from init_unreal to handle the Python startup process
    """
    # Ensure startup only run once
    global post_startup_id
    if post_startup_id:
        print("Package has already been initialized!")
        return

    # register and cache the post_startup callback and then run pre_startup
    post_startup_id = unreal.register_slate_post_tick_callback(asset_registry_callback)
    pre_startup()


def pre_startup():
    print(f"running pre startup, is asset registry available? {not asset_registry.is_loading_assets()}")
    menus.populate_menus()


def post_startup():
    """
    post startup occurs after the Asset Registry has loaded all Content Browser assets

    It should be safe to run any Python logic within Unreal at this point
    """
    print(f"running post startup, is asset registry available? {not asset_registry.is_loading_assets()}")
    editor_tools.startup()


def shutdown():
    editor_tools.shutdown()


def asset_registry_callback(ignore=None):
    """
    call post_startup() once the Asset Registry is fully loaded
    This function handles the cache and will also set up the shutdown callback
    """
    # check the asset registry
    if asset_registry.is_loading_assets():
        print("Asset Registry scan is still in progress...")
        return

    # unregister the callback
    global post_startup_id
    if post_startup_id:
        unreal.unregister_slate_post_tick_callback(post_startup_id)

    # run post startup
    post_startup()

    # register and cache the shutdown callback
    print("Registering Python Shutdown callback: startup_shutdown.shutdown()")
    global shutdown_id
    if not shutdown_id:
        shutdown_id = unreal.register_python_shutdown_callback(shutdown)
