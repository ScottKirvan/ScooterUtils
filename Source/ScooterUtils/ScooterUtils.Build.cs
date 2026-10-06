// Copyright Epic Games, Inc. All Rights Reserved.

using System;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text.RegularExpressions;
using UnrealBuildTool;

public class ScooterUtils : ModuleRules
{
	public ScooterUtils(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PrivateIncludePaths.Add(GenerateBuildInfo());

		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);


		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);


		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
			}
			);


		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"EditorStyle",
				"UnrealEd",
				"InputCore",
				"LevelEditor",
				"ToolMenus",
				"PropertyEditor",
				"Json",
				"JsonUtilities",
				"Projects",
				// ... add private dependencies that you statically link with here ...
			}
			);


		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);

		// DesktopPlatform is only available for Editor and Program targets (running on a desktop platform)
		bool IsDesktopPlatformType = Target.Platform == UnrealBuildTool.UnrealTargetPlatform.Win64
			|| Target.Platform == UnrealBuildTool.UnrealTargetPlatform.Mac
			|| Target.Platform == UnrealBuildTool.UnrealTargetPlatform.Linux;
		if (Target.Type == TargetType.Editor || (Target.Type == TargetType.Program && IsDesktopPlatformType))
		{
			PrivateDependencyModuleNames.AddRange(
				new string[] {
					"DesktopPlatform",
				}
			);
		}
	}

	// The timestamp is only refreshed when the branch or a module source file changes, so it is the time the module
	// was last rebuilt without forcing a recompile on every UBT run.
	private string GenerateBuildInfo()
	{
		string branch = ResolveGitBranch();
		long newestSourceTicks = Directory.GetFiles(ModuleDirectory, "*", SearchOption.AllDirectories)
			.Select(file => File.GetLastWriteTimeUtc(file).Ticks)
			.DefaultIfEmpty(0)
			.Max();
		string key = branch + "|" + newestSourceTicks;

		string directory = Path.Combine(PluginDirectory, "Intermediate", "BuildInfo");
		string header = Path.Combine(directory, "ScooterUtilsBuildInfo.generated.h");
		string keyLine = "// key: " + key;

		if (!File.Exists(header) || File.ReadLines(header).FirstOrDefault() != keyLine)
		{
			Directory.CreateDirectory(directory);
			File.WriteAllText(header, string.Join("\n", new string[]
			{
				keyLine,
				"#pragma once",
				"#define SCOOTER_UTILS_BUILD_BRANCH TEXT(\"" + branch + "\")",
				"#define SCOOTER_UTILS_BUILD_TIME_UTC TEXT(\"" + DateTime.UtcNow.ToString("yyyy-MM-dd HH:mm") + "\")",
				""
			}));
		}

		return directory;
	}

	private string ResolveGitBranch()
	{
		string branch = null;
		string topLevel = RunGit("rev-parse --show-toplevel");
		if (topLevel != null && PathsMatch(topLevel, PluginDirectory))
		{
			branch = RunGit("rev-parse --abbrev-ref HEAD");
		}

		if (string.IsNullOrEmpty(branch) && Environment.GetEnvironmentVariable("GITHUB_REF_TYPE") == "branch")
		{
			branch = Environment.GetEnvironmentVariable("GITHUB_HEAD_REF");
			if (string.IsNullOrEmpty(branch))
			{
				branch = Environment.GetEnvironmentVariable("GITHUB_REF_NAME");
			}
		}

		if (string.IsNullOrEmpty(branch) || branch == "HEAD")
		{
			return "";
		}

		return Regex.Replace(branch, @"[^A-Za-z0-9._/+@#-]", "_");
	}

	private string RunGit(string arguments)
	{
		try
		{
			ProcessStartInfo startInfo = new ProcessStartInfo("git", arguments)
			{
				WorkingDirectory = PluginDirectory,
				RedirectStandardOutput = true,
				RedirectStandardError = true,
				UseShellExecute = false,
				CreateNoWindow = true
			};

			using (Process process = Process.Start(startInfo))
			{
				string output = process.StandardOutput.ReadToEnd().Trim();
				process.StandardError.ReadToEnd();
				if (!process.WaitForExit(5000) || process.ExitCode != 0)
				{
					return null;
				}
				return output;
			}
		}
		catch (Exception)
		{
			return null;
		}
	}

	private static bool PathsMatch(string a, string b)
	{
		string Normalize(string path) => Path.GetFullPath(path).TrimEnd('/', '\\');
		return string.Equals(Normalize(a), Normalize(b), StringComparison.OrdinalIgnoreCase);
	}
}
