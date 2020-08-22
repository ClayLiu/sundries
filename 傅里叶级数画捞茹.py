from long_fourier_scenes_copy import FourierOfFourier, FourierOfFourierZoomedIn, FourierOfFourier100xZoom
from active_projects.diffyq.part4.fourier_series_scenes import IncreaseOrderOfApproximation
from active_projects.diffyq.part2.fourier_series import FourierCirclesScene, FourierHeart, FourierOfTrebleClef



fs_file_name = "fs_2"
fs_CONFIG = {
    "file_name": fs_file_name
}

class Shadow(IncreaseOrderOfApproximation):
    CONFIG = {
        "file_name": "shadow",
        "n_vectors": 128
    }

class Shadow_no_little(FourierOfTrebleClef):
    CONFIG = {
        "n_vectors": 120,
        "run_time": 20,
        "start_drawn": True,
        "file_name": "shadow",
        "height": 7.5,
    }

class FourierOfFanShu(FourierOfFourier):
    CONFIG = {
        "n_vectors": 300,
        "file_name": fs_file_name
    }

class FanShu(IncreaseOrderOfApproximation):
    CONFIG = fs_CONFIG

class FanShu100xZoom(FourierOfFourier100xZoom):
    CONFIG = fs_CONFIG

class FanShuZoomIn(FourierOfFourierZoomedIn):
    CONFIG = fs_CONFIG


