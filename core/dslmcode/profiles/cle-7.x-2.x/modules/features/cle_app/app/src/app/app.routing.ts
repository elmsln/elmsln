import { ModuleWithProviders } from '@angular/core';
import { Routes, RouterModule } from '@angular/router';

import { AppComponent } from './app.component';
import { DashboardComponent } from './dashboard/dashboard.component';
import { AssignmentListComponent } from './assignment/assignment-list/assignment-list.component';
import { AssignmentComponent } from './assignment/assignment.component';
import { SubmissionListComponent } from './submission/submission-list/submission-list.component';
import { SubmissionComponent } from './submission/submission.component';
import { CritiqueComponent } from './critique/critique.component';

const appRoutes: Routes = [
  {
    path: '',
    redirectTo: '/submissions',
    pathMatch: 'full'
  },
  {
    path: 'dashboard',
    component: DashboardComponent
  },
  {
    path: 'assignments',
    component: AssignmentListComponent
  },
  {
    path: 'assignments/:id',
    component: AssignmentComponent
  },
  {
    path: 'submissions',
    component: SubmissionListComponent
  },
  {
    path: 'submissions/:id',
    component: SubmissionComponent
  }
];

export const appRoutingProviders: any[] = [

];

export const routing: ModuleWithProviders = RouterModule.forRoot(appRoutes);
