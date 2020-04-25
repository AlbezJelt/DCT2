#include "DCT2.h"
#include "include/Eigen/Core"
#include <gtkmm-3.0/gtkmm.h>

#include <iostream>
#include <chrono>
#include <random>

static void
activate(GtkApplication *app, gpointer user_data)
{
  GtkWidget *window;
  GtkWidget *button;
  GtkWidget *button_box;

  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "Window");
  gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);

  button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
  gtk_container_add (GTK_CONTAINER (window), button_box);

  button = gtk_file_chooser_button_new (("Select a file"),
                                        GTK_FILE_CHOOSER_ACTION_OPEN);
  gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER (button),
                                       "./");
  gtk_container_add (GTK_CONTAINER (button_box), button);

  gtk_widget_show_all(window);
}

int main(int argc, char **argv)
{
  GtkApplication *app;
  int status;

  app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}

void test_project_matrix()
{
  Eigen::MatrixXd test(8, 8);
  test << 231, 247, 234, 193, 11, 97, 193, 87,
      32, 40, 202, 190, 24, 195, 70, 149,
      233, 248, 245, 100, 210, 203, 174, 57,
      161, 245, 167, 167, 177, 47, 167, 192,
      24, 124, 9, 43, 81, 125, 41, 65,
      71, 204, 217, 180, 243, 114, 30, 129,
      140, 36, 239, 8, 8, 165, 127, 178,
      245, 107, 173, 70, 112, 181, 245, 228;

  test = test.transpose().eval();

  Eigen::MatrixXd test_after_DCT2 = DCT2::DCT2_mt(test);
  Eigen::MatrixXd testDCT2_after_IDCT2 = DCT2::IDCT2_mt(test_after_DCT2);

  std::cout << test << std::endl
            << std::endl;
  std::cout << test_after_DCT2 << std::endl
            << std::endl;
  std::cout << testDCT2_after_IDCT2 << std::endl
            << std::endl;
}