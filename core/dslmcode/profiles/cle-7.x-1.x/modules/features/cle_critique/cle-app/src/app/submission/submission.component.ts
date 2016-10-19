import { Component, OnInit } from '@angular/core';
import { ActivatedRoute, Params } from '@angular/router';
import { Location } from '@angular/common';
import { SubmissionService } from '../submission.service';

@Component({
  selector: 'cle-submission',
  templateUrl: './submission.component.html',
  styleUrls: ['./submission.component.css'],
  providers: [SubmissionService]
})
export class SubmissionComponent implements OnInit {
  submissionId: number;
  submission: any;
  author: any;

  constructor(
    private route: ActivatedRoute,
    private location: Location,
    private submissionService: SubmissionService
  ) { }

  ngOnInit() {
    this.route.params.forEach((params: Params) => {
      let id = +params['id'];
      this.submissionId = id;
    });

    if (this.submissionId) {
      this.submissionService.getSubmission(this.submissionId)
        // @todo figure out why I have to use flatMap. It's treating the array
        // of submissions that we are getting from the service not as a typical
        // Observable of an array. I'm pretty sure that flapMap is a hack to get
        // it to work but will come with over complications, like possibly
        // inadvertently combining streams.
        // .flatMap(data => data)
        // .filter((data, index) => data.nid === String(this.submissionId))
        .subscribe(data => console.log(data));
    }

  }
}
