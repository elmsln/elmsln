import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';
import { FormsModule, ReactiveFormsModule } from '@angular/forms';
import { HttpModule } from '@angular/http';
import 'rxjs/add/operator/map';
import { routing } from './app.routing';

// material
import { MaterialModule } from '@angular/material';
import { NKDatetimeModule } from 'ng2-datetime/ng2-datetime';

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
import { DatepickerComponent } from './datepicker/datepicker.component';
import { AssignmentFormComponent } from './assignment/assignment-form/assignment-form.component';
import { ProjectsComponent } from './projects/projects.component';
import { ProjectsListComponent } from './projects/projects-list/projects-list.component';
import { DropdownComponent } from './components/dropdown/dropdown.component';
import { ProjectCardComponent } from './projects/project-card/project-card.component';
import { ProjectItemComponent } from './projects/project-item/project-item.component';
import { EditableFieldComponent } from './editable-field/editable-field.component';
import { DatetimeInputComponent } from './datetime-input/datetime-input.component';

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
    WysiwygjsComponent,
    DatepickerComponent,
    AssignmentFormComponent,
    ProjectsComponent,
    ProjectsListComponent,
    DropdownComponent,
    ProjectCardComponent,
    ProjectItemComponent,
    EditableFieldComponent,
    DatetimeInputComponent
  ],
  imports: [
    BrowserModule,
    FormsModule,
    ReactiveFormsModule,
    HttpModule,
    routing,
    MaterialModule.forRoot(),
    MomentModule,
    NKDatetimeModule
  ],
  providers: [
    ElmslnService,
    CritiqueService
  ],
  bootstrap: [AppComponent]
})
export class AppModule { }
