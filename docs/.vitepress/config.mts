import { defineConfig } from 'vitepress'

export default defineConfig({
  title: "ScooterUtils",
  description: "Unreal Engine utility plugin for developers",
  base: '/ScooterUtils/',
  themeConfig: {
    nav: [
      { text: 'Home', link: '/' },
      { text: 'User Guide', link: '/guide/' },
      { text: 'GitHub', link: 'https://github.com/ScottKirvan/ScooterUtils' }
    ],
    sidebar: {
      '/guide/': [
        {
          text: 'User Guide',
          items: [
            { text: 'Overview', link: '/guide/' },
            { text: 'Installing and Enabling', link: '/guide/installing' },
            { text: 'Menus and Toolbar', link: '/guide/editor-menus' },
            { text: 'Editor Preferences', link: '/guide/editor-preferences' }
          ]
        },
        {
          text: 'Blueprint Nodes',
          items: [
            { text: 'Blueprint Nodes Overview', link: '/guide/blueprint-nodes/' },
            { text: 'Global Config', link: '/guide/blueprint-nodes/global-config' },
            { text: 'File IO', link: '/guide/blueprint-nodes/file-io' },
            { text: 'Debug Print', link: '/guide/blueprint-nodes/debug-print' },
            { text: 'Blueprint Reflection', link: '/guide/blueprint-nodes/blueprint-reflection' },
            { text: 'Lorem Ipsum', link: '/guide/blueprint-nodes/lorem-ipsum' },
            {
              text: 'JSON',
              collapsed: false,
              items: [
                { text: 'JSON Overview', link: '/guide/blueprint-nodes/json/' },
                { text: 'Creation Nodes', link: '/guide/blueprint-nodes/json/creation' },
                { text: 'Parsing Nodes', link: '/guide/blueprint-nodes/json/parsing' },
                { text: 'Examples and Troubleshooting', link: '/guide/blueprint-nodes/json/examples' }
              ]
            }
          ]
        }
      ]
    },
    outline: {
      level: [2, 3],
      label: 'On this page'
    },
    socialLinks: [
      { icon: 'github', link: 'https://github.com/ScottKirvan/ScooterUtils' },
      { icon: 'discord', link: 'https://discord.gg/TN6XJSNK5Y' }
    ],
    search: {
      provider: 'local'
    }
  }
})
