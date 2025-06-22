using System.Windows;
using System.IO;

namespace Browser.Source.Entry
{
    public static class Entry
    {
        public static DirectoryInfo? NewDir(string path, string dirName)
        {
            DirectoryInfo info;
            try
            {
                string home = Path.Combine(path, dirName);
                info = Directory.CreateDirectory(home);
            }
            catch
            {
                Console.Error.WriteLine("The caller does not have required permission to create directory!");
                return null;
            }

            return info;
        }

        /// <summary>
        /// Creates a new TomTek project at a given path.
        /// </summary>
        /// <param name="name">The name of the project</param>
        /// <param name="path">Where the project should be parented to</param>
        public static void CreateNewProject(string name, string path)
        { 
            //Guard just incase the path is invalid or not qualified.
            string fullPath = Path.GetFullPath(path);
            if (fullPath == null)
            {
                throw new Exception("Path passed is invalid.");
            }
            
            if (!Path.IsPathFullyQualified(path))
            {
                throw new Exception("Path passed is not fully qualified!");
            }

            if (Directory.Exists(Path.Combine(fullPath, name)))
            {
                throw new Exception("Project already exists");
            }

            //Begin creating the project!
            DirectoryInfo? projectHome = NewDir(fullPath, name);
            if (projectHome == null)
            {
                throw new Exception("Failed to create ProjectHome directory");
            }

            try
            {
                //Create Sub Engine Directories
                NewDir(projectHome.FullName, "Content");
                NewDir(projectHome.FullName, "Intermediate");
                NewDir(projectHome.FullName, "Launcher");
            }
            catch (Exception e)
            {
                Console.Error.WriteLine(e.ToString());
            }
        }

        /// <summary>
        /// Very basic implementation which will create a new TomTek Engine project from
        /// an empty template.
        /// 
        /// Asks user for path via console then creates a TomTek Project at that paths directory.
        /// </summary>
        /// <param name="args"></param>
        public static void Main(string[] args)
        {
            Console.WriteLine("New Project Name: ");
            string? projName = Console.ReadLine();
            if (projName == null)
            {
                Console.Error.WriteLine("Invalid name for project");
                return;
            }

            Console.WriteLine("New Project Directory Path: ");
            string? dir = Console.ReadLine();
            if (dir == null)
            {
                Console.Error.WriteLine("Invalid input for path.");
                return;
            }

            CreateNewProject(projName, dir);




            Console.WriteLine("Press any key to exit program.");
            Console.ReadLine();
        }
    }
}
