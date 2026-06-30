Import("env")

import os

def get_linker(env) -> str:
    linker_scripts: dict = {
        "esp32": "conf/faf_linker_espressif32.ld",
        "native": "conf/faf_linker_native.ld"
    }

    lib_path: str = os.path.join(env.subst("$PROJECT_LIBDEPS_DIR"), env.get("PIOENV"), "faf")
    board_mcu: str = env.BoardConfig().get("build.mcu", "").lower()

    print(f"FAF: Board Environment -> {board_mcu}.")
    
    ld_file: str = linker_scripts.get(board_mcu)
    ld_final_path: str = ""
    
    if ld_file:
        print("FAF: Linker Espressif32 Enabled.")
        ld_final_path = os.path.join(lib_path, ld_file)
    else:
        print(f"FAF: Platform >{board_mcu}< Not Supported! Using Native Fallback.")
        ld_final_path = os.path.join(lib_path, (linker_scripts.get("native")))
    
    return ld_final_path

script: str = get_linker(env)
env.Append(LINKFLAGS=["-Wl,-T" + script])