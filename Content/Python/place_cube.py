import math
import unreal


def spawn_cube(location = unreal.Vector(), rotation = unreal.Rotator()):
    # Get the system to control the actors
    editor_actor_subs = unreal.get_editor_subsystem(unreal.EditorActorSubsystem)

    # We want to create a static mesh actor
    actor_class = unreal.StaticMeshActor

    # Place it in the level
    static_mesh_actor = editor_actor_subs.spawn_actor_from_class(actor_class, location, rotation)

    # Load and add the cube to it
    static_mesh = unreal.EditorAssetLibrary.load_asset("/Engine/BasicShapes/Cube.Cube")
    static_mesh_actor.static_mesh_component.set_static_mesh(static_mesh)


def spawn_cubes_in_circle(cube_amount, circle_radius):
    circle_center = unreal.Vector(0, 0, 0)

    for i in range(cube_amount):
        circle_x_location = circle_radius * math.cos(math.radians(i * 360 / cube_amount))
        circle_y_location = circle_radius * math.sin(math.radians(i * 360 / cube_amount))
        circle_z_location = i * 100

        location = unreal.Vector(circle_x_location, circle_y_location, circle_z_location)

        location_to_circle_center = location - circle_center
        rotation = location_to_circle_center.quaternion().rotator()

        spawn_cube(location, rotation)

def __main__():
    cube_amount = 20
    circle_radius = 1000
    spawn_cubes_in_circle(cube_amount, circle_radius)


if __name__ == "__main__":
    with unreal.ScopedEditorTransaction("Place cube") as _:
        __main__()
