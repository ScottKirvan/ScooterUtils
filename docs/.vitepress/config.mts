import { defineConfig } from 'vitepress'

export default defineConfig({
  title: "ScooterUtils",
  description: "Unreal Engine utility plugin for developers",
  base: '/ScooterUtils/',
  themeConfig: {
    nav: [
      { text: 'Home', link: '/' },
      { text: 'GitHub', link: 'https://github.com/ScottKirvan/ScooterUtils' }
    ],
    socialLinks: [
      { icon: 'github', link: 'https://github.com/ScottKirvan/ScooterUtils' },
      { icon: 'discord', link: 'https://discord.gg/TN6XJSNK5Y' }
    ]
  }
})
