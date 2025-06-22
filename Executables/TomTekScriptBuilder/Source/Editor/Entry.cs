using System;
using System.Diagnostics;
using System.IO;
using System.Net.Http.Headers;
using System.Reflection;
using System.Xml.Linq;
using Microsoft.CodeAnalysis;
using Microsoft.CodeAnalysis.CSharp;
using Microsoft.CodeAnalysis.CSharp.Syntax;
using Microsoft.CodeAnalysis.Text;


namespace TomTekEditor.ScriptBuilder
{
    class Entry
    {

        private static readonly string k_ScriptDllFileName = "Everything"; //i thought this was funny
        private static readonly string k_DevDebugProjectPath = "C:/Users/Liam/Documents/TomTek Projects/Scripting";

        /// <summary>
        /// Entry point for compiler application
        /// </summary>
        /// <param name="args">When in release mode, path to project that needs code compilation must be first parameter</param>
        /// <returns></returns>
        /// <exception cref="Exception"></exception>
        private static int Main(string[] args)
        {
            // Get target project directory to compile the scripts for
            string dir = String.Empty;
        #if NDEBUG
            
            if (args.Length == 0)
            {
                Console.Error.WriteLine("Missing neccessary command arguments for ScriptBuilder");
                return 1;
            }

            //First command argument should be the path to the directory of the
            //TomTek project which needs it's code compiled
            dir = args[0];

        #else

            //Since we're debugging we're going to ask the developer running this
            //application which TomTek project should have it's C# code compiled.
            Console.WriteLine("Hard coding debug path...");
            dir = k_DevDebugProjectPath;


        #endif

            //Make sure the directory is valid
            if (!Path.IsPathFullyQualified(dir))
            {
                throw new Exception("Path passed is not fully qualified!");
            }

            //Time compilation for debug purposes
            Stopwatch compileDuration = Stopwatch.StartNew();

            //Gather the syntax trees for compilation
            //Make sure all syntax trees were gather successfully before proceeding.
            List<SyntaxTree> trees = GetSyntaxTrees(dir);
            
            //Actually compile the C# code to a DLL which can be used by Mono when needed.
            //Assuming no exceptions occur a MemoryStream will be returned containing all GameCode
            //compiled into a single DLL file
            MemoryStream compiledMemoryStream = FromSyntaxTreesCompileToDll(trees);
            //Output's the game code to a DLL file on the user's computer. The DLL will be placed within
            //the directory of the TomTek Project
            OutputDllToProject(dir, compiledMemoryStream);
            
            compileDuration.Stop();
            Console.WriteLine($"Compilation took: {compileDuration.ElapsedMilliseconds}ms");

        #if DEBUG
            Console.ReadLine(); //yield until developer closes console...
        #endif //DEBUG

            return 0;
        }

        /// <summary>
        /// Margin for error to occur! Possible that exception is thrown.
        /// Given a directory to a project, it will open the "Contents" directory and begin
        /// reading every single C# file. The contents of each C# file will be each individually put within
        /// a SyntaxTree.
        /// </summary>
        /// <param name="projectDir">The directory to the project which wishes to have it's game code compiled</param>
        /// <returns>Each SyntaxTree which will be sent to the compiler</returns>
        private static List<SyntaxTree> GetSyntaxTrees(string projectDir)
        {
            //Enter into the content directory.
            //Double check to see if the directory is valid. If not throw an exception
            string contentDir = Path.Combine(projectDir, "Content");
            if (!Path.IsPathFullyQualified(contentDir))
            {
                throw new Exception($"Failed to open directory Content in TomTek Project '{projectDir}'");
            }

            List<SyntaxTree> trees = new List<SyntaxTree>();

            //Filter & iterator through every C# file within the Contents directory of the project.
            //Will iterator through descendants.
            foreach (string csFile in Directory.EnumerateFiles(contentDir, "*.cs", SearchOption.AllDirectories))
            {
                Console.WriteLine($"Generating Syntax Tree for {csFile}");

                string fileContents = File.ReadAllText(csFile);

                SyntaxTree tree = CSharpSyntaxTree.ParseText(fileContents, path: csFile);
                trees.Add(tree);
            }

            return trees;
        }

        /// <summary>
        /// Outputs the given MemoryStream of compiled game code into a DLL in the projectDir.
        /// May fail for any reason, but in most cases it shouldn't.
        /// </summary>
        /// <param name="projectDir">The project to output the DLL to</param>
        /// <param name="compiledMemoryStream">The stream of compiled code which will be pushed into the DLL</param>
        /// <exception cref="Exception"></exception>
        private static void OutputDllToProject(string projectDir, MemoryStream compiledMemoryStream)
        {
            string outputPath = Path.Combine(projectDir, $"{k_ScriptDllFileName}.dll");

            try
            {
                compiledMemoryStream.Position = 0;

                //Push into DLL file
                using (var fileStream = new FileStream(outputPath, FileMode.Create, FileAccess.Write))
                {
                    compiledMemoryStream.CopyTo(fileStream);
                }

                Console.WriteLine("Successfully exported game code to DLL");
            }
            catch (Exception ex)
            {
                throw new Exception($"Failed to write DLL to {outputPath}: {ex.Message}", ex);
            }
            finally
            {
                compiledMemoryStream.Dispose();
            }
        }

        /// <summary>
        /// Serves the purpose of compiling a list of SyntaxTrees into a DLL
        /// The MemoryStream returned is the stream of compiled code which can be used
        /// to be outputed within a DLL file.
        /// To output into a DLL file use OutputDllToProject()
        /// </summary>
        /// <param name="trees">List of trees to compile</param>
        /// <returns></returns>
        /// <exception cref="Exception"></exception>
        private static MemoryStream FromSyntaxTreesCompileToDll(List<SyntaxTree> trees)
        {
            MetadataReference[] references =
            {
                MetadataReference.CreateFromFile(typeof(object).Assembly.Location),
                MetadataReference.CreateFromFile(typeof(Console).Assembly.Location),
                MetadataReference.CreateFromFile(Assembly.Load("System.Runtime").Location),
                MetadataReference.CreateFromFile(Assembly.Load("System.Private.CoreLib").Location),
                MetadataReference.CreateFromFile(Assembly.Load("netstandard").Location),
                MetadataReference.CreateFromFile(Assembly.GetExecutingAssembly().Location)
            };

            //Setup compiler.
            CSharpCompilation compilation = CSharpCompilation.Create(
                k_ScriptDllFileName,
                [.. trees],
                references,
                new CSharpCompilationOptions(
                    OutputKind.DynamicallyLinkedLibrary,
                    optimizationLevel: OptimizationLevel.Debug
                )
            );

            //Try and compile everything into the memory stream. If something goes wrong
            //throw and exception.
            //Otherwise return out of the function with the MemoryStream containing the game code
            MemoryStream memoryStream = new MemoryStream();
            Microsoft.CodeAnalysis.Emit.EmitResult result = compilation.Emit(memoryStream);
            if ( !result.Success )
            {
                foreach (var diagnostic in result.Diagnostics)
                {
                    Console.WriteLine(diagnostic.ToString());
                }
                throw new Exception("There was an issue compiling game code!");
            }

            return memoryStream;
        }
    }
}