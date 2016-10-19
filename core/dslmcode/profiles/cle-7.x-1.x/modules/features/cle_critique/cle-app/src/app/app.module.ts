import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';
import { FormsModule } from '@angular/forms';
import { HttpModule } from '@angular/http';
import 'rxjs/add/operator/map';

import { routing } from './app.routing';

import { MaterialModule } from '@angular/material';
import { MaterializeDirective } from "angular2-materialize";

import { AppComponent } from './app.component';
import { AssignmentComponent } from './assignment/assignment.component';
import { AssignmentListComponent } from './assignment/assignment-list/assignment-list.component';
import { DashboardComponent } from './dashboard/dashboard.component';
import { SubmissionComponent } from './submission/submission.component';
import { SubmissionListComponent } from './submission/submission-list/submission-list.component';
import { UserComponent } from './user/user.component';
import { CritiqueComponent } from './critique/critique.component';

@NgModule({
  declarations: [
    AppComponent,
    AssignmentComponent,
    AssignmentListComponent,
    DashboardComponent,
    SubmissionComponent,
    SubmissionListComponent,
    UserComponent,
    CritiqueComponent,
    MaterializeDirective
  ],
  imports: [
    BrowserModule,
    FormsModule,
    HttpModule,
    routing,
    MaterialModule.forRoot()
  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }
