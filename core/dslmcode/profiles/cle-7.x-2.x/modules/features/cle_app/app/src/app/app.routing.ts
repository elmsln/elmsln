import { ModuleWithProviders } from '@angular/core';
import { Routes, RouterModule } from '@angular/router';

import { AppComponent } from './app.component';
import { DashboardComponent } from './dashboard/dashboard.component';
import { AssignmentListComponent } from './assignment/assignment-list/assignment-list.component';
import { AssignmentComponent } from './assignment/assignment.component';
import { AssignmentFormComponent } from './assignment/assignment-form/assignment-form.component';
import { SubmissionListComponent } from './submission/submission-list/submission-list.component';
import { SubmissionComponent } from './submission/submission.component';
import { CritiqueComponent } from './critique/critique.component';
import { LoginComponent } from './login/login.component';
import { LogoutComponent } from './logout/logout.component';
import { ProjectsListComponent } from './projects/projects-list/projects-list.component';

const appRoutes: Routes = [
  {
    path: '',
    component: AppComponent
  },
  {
    path: 'login',
    component: LoginComponent
  },
  {
    path: 'logout',
    component: LogoutComponent
  },
  {
    path: 'projects',
    component: ProjectsListComponent
  },
  {
    path: 'assignments/:id',
    component: AssignmentComponent
  }
];

export const appRoutingProviders: any[] = [

];

export const routing: ModuleWithProviders = RouterModule.forRoot(appRoutes);
