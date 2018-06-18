examples_dir = join_paths(clutter_datadir, clutter_api_name, 'cookbook', 'examples')

all_examples = [
  ['actors-composite-main', ['cb-button.c'], ['cb-button.h']],
  ['animations-complex'],
  ['animations-looping-animator'],
  ['animations-looping-implicit'],
  ['animations-looping-state'],
  ['animations-moving-animator'],
  ['animations-moving-implicit'],
  ['animations-moving-state'],
  ['animations-path'],
  ['animations-path-circle'],
  ['animations-reuse'],
  ['animations-rotating'],
  ['animations-scaling'],
  ['animations-scaling-zoom'],
  ['effects-basic', ['cb-border-effect.c', 'cb-background-effect.c'], ['cb-border-effect.h', 'cb-background-effect.h']],
  ['effects-built-in'],
  ['effects-custom-deform', ['cb-page-fold-effect.c'], ['cb-page-fold-effect.h']],
  ['events-buttons'],
  ['events-buttons-click'],
  ['events-buttons-lasso'],
  ['events-mouse-scroll'],
  ['events-pointer-motion'],
  ['events-pointer-motion-crossing'],
  ['events-pointer-motion-stacked'],
  ['events-pointer-motion-scribbler'],
  ['layouts-bind-constraint-allocation'],
  ['layouts-bind-constraint-overlay'],
  ['layouts-bind-constraint-stage'],
  ['layouts-box'],
  ['layouts-box-menu'],
  ['layouts-box-property-effects'],
  ['layouts-stacking'],
  ['layouts-stacking-diff-sized-actors'],
  ['script-ui'],
  ['script-signals'],
  ['script-states'],
  ['text-shadow'],
  ['textures-crossfade'],
  ['textures-crossfade-cogl'],
  ['textures-crossfade-slideshow'],
  ['textures-reflection'],
  ['textures-split-go'],
  ['textures-sub-texture'],
]

example_data = []
foreach e: all_examples
  example_src = [ e[0] + '.c' ] + e.get(1, [])
  example_bin = executable(e[0],
    example_src,
    dependencies: [libclutter_dep, mathlib_dep],
    c_args: [
      '-DG_DISABLE_SINGLE_INCLUDES',
      '-DGLIB_DISABLE_DEPRECATION_WARNINGS',
      '-DCOGL_DISABLE_DEPRECATION_WARNINGS',
      '-DCLUTTER_DISABLE_DEPRECATION_WARNINGS',
    ],
    link_args: ['-export-dynamic'],
  )

  example_data += files(example_src, e.get(2, []))
endforeach

ui_data = [
  'animations-complex.json',
  'animations-complex-overlapping.json',
  'animations-reuse-animation.json',
  'animations-reuse-ui.json',
  'script-signals.json',
  'script-states.json',
  'script-ui.json',
]

img_data = [
  'redhand.png',
  'smiley.png',
]

install_data(example_data + ui_data + img_data,
  install_dir: examples_dir,
)
