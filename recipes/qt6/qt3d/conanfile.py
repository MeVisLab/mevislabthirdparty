from conan import ConanFile


required_conan_version = ">=2.2.2"

class ConanRecipe(ConanFile):
    python_requires = "qt_package/1.0.0"
    python_requires_extend = "qt_package.QtPackage"

    mlab_hooks = {
        'dependencies.system_libs': [
            'libxkbcommon.so.0',
        ]
    }

    qt_feature = {
		"opengl": True,
		"qt3d_animation": True,
		"qt3d_extras": True,
		"qt3d_input": True,
		"qt3d_logic": True,
		"qt3d_render": True,
		"qt3d_rhi_renderer": True,
		"qt3d_system_assimp": True,
		"regularexpression": True,
		"system_zlib": True,
		"vulkan": True,
    }

    def requirements(self):
        super().requirements()
        self.requires(f"zlib/[>=1.2.13]")
        self.requires(f"assimp/[>=5.0.0]")
