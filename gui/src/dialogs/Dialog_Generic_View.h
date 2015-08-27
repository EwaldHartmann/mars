/*
 *  Copyright 2011, 2012, DFKI GmbH Robotics Innovation Center
 *
 *  This file is part of the MARS simulation framework.
 *
 *  MARS is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License
 *  as published by the Free Software Foundation, either version 3
 *  of the License, or (at your option) any later version.
 *
 *  MARS is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *   You should have received a copy of the GNU Lesser General Public License
 *   along with MARS.  If not, see <http://www.gnu.org/licenses/>.
 *
 */


//Dialog_Generic_View.h

#ifndef DIALOG_GENERIC_VIEW_H
#define DIALOG_GENERIC_VIEW_H

#ifdef _PRINT_HEADER_
#warning "Dialog_Generic_View.h"
#endif

#include <mars/main_gui/BaseWidget.h>
#include <mars/main_gui/PropertyDialog.h>
#include <mars/interfaces/sim/ControlCenter.h>
#include <mars/interfaces/graphics/GraphicsEventClient.h>
#include <mars/interfaces/core_objects_exchange.h>
#include "NodeHandler.h"
#include <QTreeWidget>
#include <QLabel>
#include <QFrame>


namespace mars {
  namespace gui {

  class Dialog_Generic_View : public main_gui::BaseWidget,
                              public main_gui::PropertyCallback,
                              public interfaces::GraphicsEventClient {
      Q_OBJECT

      public:
      Dialog_Generic_View(interfaces::ControlCenter *c, QWidget *parent = NULL);
      ~Dialog_Generic_View();
  
      main_gui::PropertyDialog *pDialog;  
  
      virtual void selectEvent(unsigned long int id, bool mode);

      // returns the ids of the selected nodes
      std::vector<unsigned long> selectedNodes(void);
  
    private:
      interfaces::ControlCenter *control;
      bool filled, select_allowed;
      QtVariantProperty *node_view_mode, *node_selection_mode, *root ;
  
      std::vector<interfaces::core_objects_exchange> simNodes;
      std::vector<unsigned long> present;

      QTreeWidget *treeWidget;
      QLabel *label;
      QFrame *line;

      void closeEvent(QCloseEvent* event);
      void fill(unsigned long id, QTreeWidgetItem *current = NULL);
      void selectRecursively(QTreeWidgetItem *current, bool mode);
      QTreeWidgetItem* findByNodeId(unsigned long id, QTreeWidgetItem *parent = NULL);
      void reset(void);
      void createTree(unsigned long root);
      void createList(void);
  
    signals:
      void closeSignal(void* widget);
      void itemSelectionChanged();

    private slots:
      virtual void valueChanged(QtProperty *property, const QVariant &value);
      void selectNodes(void);

    };  } // end of namespace gui
} // end of namespace mars

#endif // DIALOGNODES_H
