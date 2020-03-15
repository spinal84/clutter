subdir('examples')

xml_files = [
  'actors.xml',
  'animations.xml',
  'events.xml',
  'introduction.xml',
  'text.xml',
  'textures.xml',
  'layouts.xml',
  'script.xml',
  'effects.xml',
]

xsltproc_options = [
  '--stringparam', 'html.stylesheet', 'style.css',
  '--stringparam', 'chapter.autolabel', '1',
  '--stringparam', 'appending.autolabel', '1',
  '--stringparam', 'section.autolabel', '1',
  '--stringparam', 'gtkdoc.bookname', 'clutter-cookbook',
  '--stringparam', 'gtkdoc.version', clutter_api_version,
  '--stringparam', 'callout.graphics', '0',
  '--path', join_paths(meson.current_source_dir()),
  '--xinclude',
]

xsltproc = find_program('xsltproc', required: false)

docbook_xsl = 'http://docbook.sourceforge.net/release/xsl/current/xhtml/docbook.xsl'

cookbook_xml_conf = configuration_data()
cookbook_xml_conf.set('CLUTTER_API_VERSION', clutter_api_version)

cookbook_dir = join_paths(clutter_datadir, 'gtk-doc', 'html')

if xsltproc.found()
  cmd = run_command([xsltproc, '--nonet', docbook_xsl])
  have_docbook_xsl = cmd.returncode() == 0

  if have_docbook_xsl
    custom_target('clutter-cookbook',
      command: [
        xsltproc,
        xsltproc_options,
        '-o', '@OUTPUT@/',
        'cookbook.xsl',
        '@INPUT@',
      ],
      input: configure_file(
        input: 'clutter-cookbook.xml.in',
        output: 'clutter-cookbook.xml',
        configuration: cookbook_xml_conf,
      ),
      output: 'clutter-cookbook',
      install_dir: cookbook_dir,
    )

    install_data('style.css', install_dir: join_paths(cookbook_dir, 'clutter-cookbook'))
    install_subdir('images', install_dir: join_paths(cookbook_dir, 'clutter-cookbook'))
    install_subdir('videos', install_dir: join_paths(cookbook_dir, 'clutter-cookbook'))
  else
    message('Cookbook not available, requires Docbook XSL')
  endif
else
  message('Cookbook not available, requires xsltproc')
endif
