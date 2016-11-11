import { Component, OnInit } from '@angular/core';
import { SubmissionService } from '../../submission.service';
import { Router } from '@angular/router';

@Component({
  selector: 'cle-submission-list',
  templateUrl: './submission-list.component.html',
  styleUrls: ['./submission-list.component.css'],
  providers: [SubmissionService]
})
export class SubmissionListComponent implements OnInit {
  submissions: Array<any>;

  constructor(
    private submissionService: SubmissionService,
    private router: Router
  ) { }

  ngOnInit() {
    this.submissionService.getSubmissions()
        .subscribe(data => {
          this.submissions = data;
          console.log(data);
        });
  }

  viewSubmission(submissionID) {
    this.router.navigate(['/submissions/' + submissionID]);
  }
}
