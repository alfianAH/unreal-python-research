import unreal


def hello_world():
    print("Hello unreal")


def get_content_browser_selected_asset():
    print(unreal.EditorUtilityLibrary.get_selected_assets())


def show_dialog_window():
    return_value = unreal.EditorDialog.show_message("Hi", "apa kabar?", unreal.AppMsgType.YES_NO_YES_ALL_NO_ALL)

    match(return_value):
        case unreal.AppReturnType.YES:
            print("baik")
            
        case unreal.AppReturnType.NO:
            print("tidak")

        case unreal.AppReturnType.YES_ALL:
            print("sehat sekali")

        case unreal.AppReturnType.NO_ALL:
            print("sakit")


def manipulate_vector():
    vector1 = unreal.Vector(0, 1, 0)
    vector2 = unreal.Vector(1, 0, 1)

    print(vector1.cross(vector2))


def get_vector_distance():
    vector1 = unreal.Vector(103, 32, 0.1)
    vector2 = unreal.Vector(0, 0, 0)

    print(unreal.Vector.distance(vector1, vector2))
    

# def get_quaternion():
#     angle = unreal.Vector(0, 90, 75)

#     print(unreal.Quat.set_from_euler(angle))


get_vector_distance()
