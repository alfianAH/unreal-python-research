import unreal

from . import (
    editor_tools
)
from .unreal_systems import ToolMenus


@unreal.uclass()
class PythonMenuTool(unreal.ToolMenuEntryScript):
    name = "unique_programatic_tool_name"
    display_name = "menu display name"
    tool_tip = "tool tip message"

    def __init__(self, menu, section, insert_policy=None):
        super().__init__()

        self.init_entry(
            owner_name="story_tools",
            menu=menu.menu_name,
            section=section,
            name=self.name,
            label=self.display_name,
            tool_tip=self.tool_tip
        )

        menu.add_menu_entry_object(self)

    @unreal.ufunction(override=True)
    def execute(self, context):
        print(f"Provided context: {context}")
        return super().execute(context)


@unreal.uclass()
class EditorUtilMenuTool(PythonMenuTool):
    widget_path = "some/path"

    @unreal.ufunction(override=True)
    def execute(self, context):
        """Open the EUW when pressed"""
        print(f"Provided context: {context}")
        editor_tools.launch_editor_utility_widget(self.widget_path)


@unreal.uclass()
class StoryTool(EditorUtilMenuTool):
    name = "story_tool"
    display_name = "Story Tool"
    widget_path = "/Game/Blueprints/Widgets/Editor/StoryTool"


def populate_menus():
    populate_main_menu()


def populate_main_menu():
    main_menu = ToolMenus.find_menu("LevelEditor.MainMenu")

    demo_menu = main_menu.add_sub_menu(
        owner="story_tools",
        section_name="",
        name="story_tool",
        label="Story Tool"
    )

    section = "tools"
    StoryTool(menu=demo_menu, section=section)
