import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';
import { FormsModule, ReactiveFormsModule } from '@angular/forms';
import { HttpModule } from '@angular/http';
import 'rxjs/add/operator/map';
import { routing } from './app.routing';

// material
import { MaterialModule } from '@angular/material';

// services
import { ElmslnService } from './elmsln.service';
import { CritiqueService } from './critique.service';

// Moment.js
import { MomentModule } from 'angular2-moment';

// components
import { AppComponent } from './app.component';
import { AssignmentComponent } from './assignment/assignment.component';
import { AssignmentListComponent } from './assignment/assignment-list/assignment-list.component';
import { DashboardComponent } from './dashboard/dashboard.component';
import { SubmissionComponent } from './submission/submission.component';
import { SubmissionListComponent } from './submission/submission-list/submission-list.component';
import { UserComponent } from './user/user.component';
import { CritiqueComponent } from './critique/critique.component';
import { CritiqueFormComponent } from './critique/critique-form/critique-form.component';
import { LoginComponent } from './login/login.component';
import { LogoutComponent } from './logout/logout.component';
import { CritiqueListComponent } from './critique/critique-list/critique-list.component';
import { WysiwygjsComponent } from './wysiwygjs/wysiwygjs.component';

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
    CritiqueFormComponent,
    LoginComponent,
    LogoutComponent,
    CritiqueListComponent,
    WysiwygjsComponent
  ],
  imports: [
    BrowserModule,
    FormsModule,
    ReactiveFormsModule,
    HttpModule,
    routing,
    MaterialModule.forRoot(),
    MomentModule
  ],
  providers: [
    ElmslnService,
    CritiqueService
  ],
  bootstrap: [AppComponent]
})
export class AppModule { }
