using EngineHub.Source;
using System.Windows;

namespace EngineHub
{
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();

        }

        private void HelloWorldClicked(object sender, RoutedEventArgs e)
        {
            MyBlock.Text = sender.ToString();
            MyButton.Content = e.ToString();

            ProjectMaker.HelloWorld();
        }
    }
}